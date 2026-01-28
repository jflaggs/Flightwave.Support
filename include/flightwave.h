#pragma once

#include <condition_variable>
#include <unordered_map>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <map>

using namespace std;

/// <summary>
/// Represents a message. All IDs are non-negative. 
/// </summary>
struct Message 
{
    /// <summary>
    /// Represents the topic ID.
    /// </summary>
    int topic_id;       

    /// <summary>
    /// Represents the order of the message within a topic.
    /// </summary>
    int sequence_num;  

    /// <summary>
    /// Represents the message. 
    /// </summary>
    std::string payload;
};

/// <summary>
/// Implements a thread safe producer/consumer system with consumption ordered by message topic.
/// </summary>
class MessageBus
{
    /*
        - Multiple producers and consumers may operate concurrently.
        - Each topic maintains its own independent sequence ordering.
    */

    private:

    struct TopicState
    {
        /// <summary>
        /// Sorted on the sequence number
        /// </summary>
        std::map<int, Message> sequenceBuffer;

        /// <summary>
        /// Each topic needs its own sequence mutex
        /// </summary>
        std::mutex sequenceMutex;

        std::condition_variable condition;
        int sequenceNumber = 0;
    };

    std::unordered_map<int, TopicState> _topics;
    std::mutex _topicsMutex;

    TopicState& get_create_topic(int id)
    {
        std::lock_guard<std::mutex> lock(_topicsMutex);

        _topics.try_emplace(id);

        return _topics[id];
    }

    public:

    MessageBus()
    {

    }

    /// <summary>
    /// Producer API. Messgages of the same topic_id are not guarenteed to be ordered by sequence number
    /// </summary>
    /// <param name="msg"></param>
    void publish(const Message& message)
    {
        // Accepts Message objects from multiple producers.
        // Messages of the same topic_id may arrive out of order.

        TopicState& state = get_create_topic(message.topic_id);

        { std::lock_guard<std::mutex> lock(state.sequenceMutex);

            state.sequenceBuffer[message.sequence_num] = message;
        }

        state.condition.notify_all();
    }

    /// <summary>
    /// Consumer API (blocking). We need to block the incoming user call, until we've recieved the next sequence_number in order starting from 0
    /// </summary>
    /// <param name="topic_id"></param>
    /// <returns></returns>
    Message get_by_topic_id(int id)
    {
        // Return the next message in order by sequence number starting from 0. 
        // Waits/Blocks until the next sequence number is recieved then returns that message.

        TopicState& state = get_create_topic(id);

        std::unique_lock<std::mutex> lock(state.sequenceMutex);

        state.condition.wait(lock, [&]() 
        { 
            // Wait until next sequence message is available

            return state.sequenceBuffer.count(state.sequenceNumber) > 0; 
        });

        Message message = state.sequenceBuffer[state.sequenceNumber];
        state.sequenceBuffer.erase(state.sequenceNumber);
        state.sequenceNumber++;

        return message;
    };
};