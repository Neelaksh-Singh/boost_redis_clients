# Boost Redis Queue Implementation

This repository contains C++ code for implementing a Redis queue, comprising a queue pusher, a queue consumer, and tests.

#### Installation Guide:

1. **Prerequisites:**
   - C++ compiler with C++11 support
   - Boost C++ Libraries
   - Redis server (for running the queue consumer and tests)

2. **Setting up Boost C++ Libraries:**
   - Download and install Boost C++ Libraries from [boost.org](https://www.boost.org/).
   - Make sure Boost is properly configured and available in your build environment.

3. **Setting up Redis Server:**
   - Install and configure Redis server on your machine. You can follow instructions from the [official Redis website](https://redis.io/download).

4. **Building the Code:**
   - Clone this repository to your local machine.
   - Navigate to the root directory of the repository.
   - Compile the code using a C++ compiler, linking against Boost Libraries. For example:
     ```
     g++ -std=c++11 queue-pusher.cpp -lboost_system -o queue-pusher
     g++ -std=c++11 queue-consumer.cpp -lboost_system -lboost_redis -o queue-consumer
     g++ -std=c++11 redis-test.cpp -lgtest -lgmock -lboost_system -o redis-test
     ```

#### Usage Guide:

1. **Queue Pusher:**
   - Compile `queue-pusher.cpp` using the provided installation guide.
   - Run the compiled executable. It will prompt you to enter data to push to the Redis queue. Press `Ctrl+D` to finish input.
   - The data entered will be pushed onto the Redis queue named `my_queue`.

2. **Queue Consumer:**
   - Compile `queue-consumer.cpp` using the provided installation guide.
   - Run the compiled executable with the following command line arguments:
     ```
     ./queue-consumer [HOST] [PORT] [Name of Queue] [optional: Number of Elements to Pop]
     ```
     Replace `[HOST]`, `[PORT]`, and `[Name of Queue]` with the appropriate values. Optionally, specify the number of elements to pop from the queue.
   - The consumer will connect to the Redis server, pop the specified number of elements from the queue, and print them.

3. **Running Tests:**
   - Compile `redis-test.cpp` using the provided installation guide.
   - Run the compiled test executable. It will execute test cases for the Producer class.
   - The tests verify that the Producer correctly sends data to the Redis queue.

#### Note:
- Make sure Redis server is running before executing the queue consumer and tests.
- Adjust Redis server configurations and connection settings as per your environment.
