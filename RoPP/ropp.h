#include <string>

#include "../include/json.hpp"

using json = nlohmann::json;
using std::string;

namespace RoPP
{
    class User
    {
        public:
            json GetFriends(string Sort="Alphabetical");
            

            User(int UID)
            {
                this->UID = UID;
            }

        private:
            int UID;
    };
}