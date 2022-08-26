#include <iostream>
#include <grpcpp/grpcpp.h>

//#include "proto/room.grpc.pb.h"
//#include "room_client.h"
#include "phone_listener.h"

#include <firebase/app.h>
#include <firebase/auth.h>
#include <firebase/future.h>

int main(int argc, char** argv)
{
    firebase::App* app = firebase::App::Create(firebase::AppOptions());

    // Get the Auth class for your App.
    firebase::auth::Auth* auth = firebase::auth::Auth::GetAuth(app);
    PhoneListener phone_listener("+19298164425", auth);
    
    while (true) {}

    /*
    auto token = "test";
    RoomClient room_client(token, grpc::CreateChannel("localhost:4444", grpc::InsecureChannelCredentials()));

    auto type = room::RoomType::PUBLIC;
    auto result = room_client.CreateRoom(type);

    std::cout << "Result received: " << result << std::endl;
    */

    return 0;
}
