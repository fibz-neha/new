#include<iostream>
#include<vector>
#include<random>

static const int MAX_TIME = 100;

struct Event {
  int time;
  std::string name;
};

struct Process {
  std::vector<Event> events;
};

int main() {
  std::system("clear");

  //Init random values
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(1, MAX_TIME);

  size_t nodes;
  std::cout << "Enter the number of physical clocks / process nodes: ";
  std::cin >> nodes;

  std::vector<Process> processes(nodes);

  for(size_t i = 0 ; i < nodes; i++) {
    int num_events;

    std::cout << "Enter the number of events for process " << i << " : ";
    std::cin >> num_events;
    processes[i].events = std::vector<Event>(num_events);

    for(int j = 0; j < num_events; j++) {
      Event& process = processes[i].events[j];

      std::cout << "Enter the name of the event: ";
      std::getline(std::cin, process.name);
      process.time = dist(mt);
      std::cout << "Event " << process.name << " Time: "<< process.time << "\n";
    }
  }
  std::cout << "=================================================\n";
  std::cout << "Timestamp of Physical Clocks:\n";
  for(size_t i = 0; i < nodes; i++) {
    std::cout << "Physical Clock " << i+1 << "\n";
    for(int j = 0; j < processes[i].events.size() ; j++) {
      std::cout << "\tEvent: " << processes[i].events[j].name << "\n";
      std::cout << "\t Physical Time: " << processes[i].events[j].time << "\n";
    }
  }
  std::cout << "=================================================\n";
  std::cout << "Lamport Logical Clock timestamps:\n";

  int timestamp = 0;
  // Calculating Logical timestamps
  for(size_t i = 0; i < MAX_TIME; i++) {
    for(size_t j = 0; j < nodes; j++) {
      for(size_t k = 0; k < processes[j].events.size(); k++) {
        if(processes[j].events[k].time == i) {
          timestamp = dist(mt) + timestamp;
          std::cout << "\t Logical Timestamp for Event " << processes[j].events[k].name << " : ";
          std::cout << timestamp << "\n";
        }
      }
    }
  }
  return 0;
}
