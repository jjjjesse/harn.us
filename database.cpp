

// https://www.youtube.com/watch?v=pWbMrx5rVBE

// MongoDB and JSON from Lee:
// https://www.youtube.com/watch?v=oQCtBFxD4QQ

// Heroku & MongoDB:
// https://forum.freecodecamp.org/t/guide-for-using-mongodb-and-deploying-to-heroku/19347

// Official MongoDB & C++
// https://www.mongodb.com/blog/post/introducing-new-c-driver
// Tutorial
// https://mongodb.github.io/mongo-cxx-driver/mongocxx-v3/tutorial/

// Install with package manager
// http://mongoc.org/libmongoc/current/installing.html


// Recommended:

#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;