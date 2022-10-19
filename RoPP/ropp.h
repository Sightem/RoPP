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
            json GetFollowers(string Sort="Asc", int Limit=10);
            json GetFollowings(string Sort="Asc", int Limit=10);


            User(int UID)
            {
                this->UID = UID;
            }

        private:
            int UID;
    };
}