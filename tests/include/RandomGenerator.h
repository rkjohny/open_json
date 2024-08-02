#include <string>
#include <random>

#ifndef OPEN_JSON_RANDOM_GENERATOR__H
#define OPEN_JSON_RANDOM_GENERATOR__H

namespace open_json_test {
    class RandomGenerator {
    private:
        // Seed with a real random value, if available
        std::random_device rd;

        std::mt19937 gen; // Standard mersenne_twister_engine
        std::uniform_int_distribution<> dis;

        char *letters = "abcdefghijklmnopqurstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        int LEN = 62;

        RandomGenerator () {
            gen = std::mt19937(rd());
            // Choose a random number between 1 and 100
            dis = std::uniform_int_distribution<>(1, 100);
        }

    public:
        static RandomGenerator& GetInstance() {
            static RandomGenerator generator;
            return generator;
        }

        int GetNextInt() {
            return dis(gen);
        }

        std::string GetNextString(int len) {
            std::string str;
            for (int i = 0; i < len; i++) {
                str += letters[GetNextInt() % 62];
            }
            return str;
        }
    };
}


#endif //OPEN_JSON_RANDOM_GENERATOR__H
