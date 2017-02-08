#pragma once

#include "../DataChannel.hpp"
#include "../ChannelEnvVars.hpp"
#include "DataChannelUtils.hpp"

#include <sys/poll.h>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <utility>

namespace thd {

struct DataChannelTCP : DataChannel {
  struct RequestTCP : DataChannel::Request {
    RequestTCP(QueueWorker::Request&& request);
    virtual ~RequestTCP();

    virtual bool isCompleted() override;
    virtual void wait() override;

  private:
    QueueWorker::Request _request;
  };

  DataChannelTCP();
  DataChannelTCP(int timeout);
  virtual ~DataChannelTCP();

  bool init() override;

  int getRank() override;
  int getNumProcesses() override;

  void allGather(std::vector<Tensor*>& output, Tensor& input, THDGroup group_id = THDGroupWORLD) override;
  void gather(std::vector<Tensor*>& output, Tensor& input,
              int dst_rank, THDGroup group_id = THDGroupWORLD) override;
  void scatter(std::vector<Tensor*>& input, Tensor& output,
               int src_rank, THDGroup group_id = THDGroupWORLD) override;
  void allReduce(Tensor& data, THDReduceOp operation,
                 THDGroup group_id = THDGroupWORLD) override;
  void reduce(Tensor& data, THDReduceOp operation, int dst_rank,
              THDGroup group_id = THDGroupWORLD) override;
  void broadcast(Tensor& data, int src_id, THDGroup group_id = THDGroupWORLD) override;
  void send(const Scalar& data, int dst_id) override;
  void send(Tensor& data, int dst_id) override;
  void receive(Scalar& data, int src_id) override;
  void receive(Tensor& data) override;
  void receive(Tensor& data, int src_id) override;
  RequestTCP* isend(Tensor& data, int dst_rank) override;
  RequestTCP* ireceive(Tensor& data, int src_rank) override;

  void barrier(THDGroup group_id = THDGroupWORLD) override;

  THDGroup newGroup(const std::vector<int>& ranks) override;

private:
  // Defines process to which master or worker is connected
  struct Process {
    std::uint32_t rank;
    std::string address;
    std::uint16_t port;
    int socket;
  };


  void listen(std::uint16_t port);
  int connect(const std::string& address, std::uint16_t port, int wait) const;
  std::tuple<int, std::string> accept() const;

  bool initMaster();
  bool initWorker();

  void _send(const Scalar& data, int dst_id);
  void _send(Tensor& data, int dst_id);
  void _receive(Scalar& data, int src_id);
  void _receive(Tensor& data, int src_id);
  void _reduce(Tensor& result, Tensor& data, THDReduceOp operation) const;
  template<typename T>
  void _reduce(Tensor& result, Tensor& data, THDReduceOp operation) const;


  int _rank; // Rank of current process, range: [0.._processes.size()-1]
  int _socket; // Socket on which process is listening
  int _port; // Port on which process is listening
  int _timeout; // Accept waiting timeout in milliseconds (it is optional, default = infinity)

  std::vector<Process> _processes; // Other processes in network
  std::unique_ptr<struct pollfd[]> _poll_events; // Events array for `poll`

  // Existing groups of processes and corresponding group ids
  std::unordered_map<THDGroup, DataChannel::Group> _groups;

  // Workers
  QueueWorker _send_worker, _receive_worker;
};

} // namespace thd
