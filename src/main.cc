#include <iostream>
#include <grpcpp/grpcpp.h>

#include "proto/room.grpc.pb.h"
#include "room_client.h"
#include "phone_listener.h"

#include "firebase/app.h"
//#include "firebase/auth.h"

int main(int argc, char** argv) {
    auto app = firebase::App::Create(firebase::AppOptions());

    auto token = "test";
    RoomClient room_client(token, grpc::CreateChannel("localhost:4444", grpc::InsecureChannelCredentials()));

    auto type = room::RoomType::PUBLIC;
    auto result = room_client.CreateRoom(type);

    std::cout << "Result received: " << result << std::endl;

    return 0;
}
