#include <grpcpp/grpcpp.h>

#include "proto/room.grpc.pb.h"

class RoomClient {
    public:
        RoomClient(const std::string& token, std::shared_ptr<grpc::Channel> channel)
            : token_{token}, stub_(room::RoomAPI::NewStub(channel)) {}

        bool CreateRoom(const room::RoomType room_type) {
            room::CreateRoomRequest request;
            request.set_type(room_type);

            room::CreateRoomResponse response;

            grpc::ClientContext context;

            grpc::Status status = stub_->CreateRoom(&context, request, &response);

            if (status.ok()) {
                return true;
            } else {
                std::cout << status.error_code() << ": " << status.error_message() << std::endl;

                return false;
            }
        }
    private:
        const std::string& token_;
        std::unique_ptr<room::RoomAPI::Stub> stub_;
};
