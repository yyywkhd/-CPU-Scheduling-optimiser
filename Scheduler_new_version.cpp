// a1810323, Siyu Huang
// a1788396, Peiyan Chen
// a1809583, Sida, Wang
// a1790760, wai tong suen
// avengers
/*
created by Andrey Kan
andrey.kan@adelaide.edu.au
2021
*/
#include <iostream>
#include <fstream>
#include <deque>
#include <vector>

// std is a namespace: https://www.cplusplus.com/doc/oldtutorial/namespaces/
const int AGE_UNIT = 35;
const int QUANTUM_0 = 1;
const int QUANTUM_1 = 20;
const int QUANTUM_2 = 30; // allow to use up to this number of time slots at once
const int PRINT_LOG = 0;          // print detailed execution trace

class Customer
{
public:
    std::string name;
    int priority;
    int arrival_time;
    int slots_remaining; // how many time slots are still needed
    int playing_since;
    int waited_time;
    int current_queue;
    int age;
    int quantum_done;

    Customer(std::string par_name, int par_priority, int par_arrival_time, int par_slots_remaining)
    {
        name = par_name;
        priority = par_priority;
        arrival_time = par_arrival_time;
        slots_remaining = par_slots_remaining;
        playing_since = -1;
        waited_time = 0;
        current_queue = -1;
        age = 0;
        quantum_done = -1;
    }
};

class Event
{
public:
    int event_time;
    int customer_id; // each event involes exactly one customer

    Event(int par_event_time, int par_customer_id)
    {
        event_time = par_event_time;
        customer_id = par_customer_id;
    }
};

void initialize_system(
    std::ifstream &in_file,
    std::deque<Event> &arrival_events,
    std::vector<Customer> &customers)
{
    std::string name;
    int priority, arrival_time, slots_requested;

    // read input file line by line
    // https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
    int customer_id = 0;
    while (in_file >> name >> priority >> arrival_time >> slots_requested)
    {
        Customer customer_from_file(name, priority, arrival_time, slots_requested);
        customers.push_back(customer_from_file);

        // new customer arrival event
        Event arrival_event(arrival_time, customer_id);
        arrival_events.push_back(arrival_event);

        customer_id++;
    }
}

void print_state(
    std::ofstream &out_file,
    int current_time,
    int current_id,
    const std::deque<Event> &arrival_events,
    const std::deque<int> &customer_queue)
{
    out_file << current_time << " " << current_id << '\n';
    if (PRINT_LOG == 0)
    {
        return;
    }
    std::cout << current_time << ", " << current_id << '\n';
    for (int i = 0; i < arrival_events.size(); i++)
    {
        std::cout << "\t" << arrival_events[i].event_time << ", " << arrival_events[i].customer_id << ", ";
    }
    std::cout << '\n';
    for (int i = 0; i < customer_queue.size(); i++)
    {
        std::cout << "\t" << customer_queue[i] << ", ";
    }
    std::cout << '\n';
}

void Remove_element(std::vector<Customer> &customers, std::deque<int> &queue_3, int customer_id)
{
    int index = 0;

    for (auto customer_ID : queue_3)
    {
        if (customer_ID == customer_id)
        {
            queue_3.erase(queue_3.begin() + index);
            return;
        }

        index++;
    }
}

void Enqueue_queue_1(std::deque<int> &queue, std::vector<Customer> &customers, int customer_id)
{
    customers[customer_id].current_queue = 1;
    customers[customer_id].quantum_done = -1;

    if (queue.empty())
    {
        queue.push_back(customer_id);
        return;
    }

    std::deque<int>::iterator it = queue.begin();
    while (it != queue.end())
    {
        if (customers[customer_id].slots_remaining < customers[*it].slots_remaining)
            break;

        ++it;
    }
    queue.insert(it, customer_id);
}

void Enqueue_queue_2(std::deque<int> &queue, std::vector<Customer> &customers, int customer_id)
{
    customers[customer_id].current_queue = 2;
    customers[customer_id].quantum_done = -1;

    if (queue.empty())
    {
        queue.push_back(customer_id);
        return;
    }

    std::deque<int>::iterator it = queue.begin();
    while (it != queue.end())
    {
        if (customers[customer_id].slots_remaining < customers[*it].slots_remaining)
            break;

        ++it;
    }
    queue.insert(it, customer_id);
}

void Enqueue_queue_3(std::deque<int> &queue, std::vector<Customer> &customers, int customer_id)
{
    customers[customer_id].current_queue = 3;

    if (queue.empty())
    {
        queue.push_back(customer_id);
        return;
    }

    std::deque<int>::iterator it = queue.begin();
    while (it != queue.end())
    {
        if (customers[customer_id].slots_remaining < customers[*it].slots_remaining)
            break;

        ++it;
    }

    queue.insert(it, customer_id);
}

void Enqueue_queue_0(std::deque<int> &queue, std::vector<Customer> &customers, int customer_id)
{
    customers[customer_id].current_queue = 0;
    queue.push_back(customer_id);
}

void Aging(std::vector<Customer> &customers, std::deque<int> &queue_1, std::deque<int> &queue_3)
{
    std::deque<int>::iterator it = queue_3.begin();

    for (auto customer_ID : queue_3)
    {
        if (customers[customer_ID].quantum_done != -1)
        {
            customers[customer_ID].waited_time = -1;
            customers[customer_ID].waited_time = 0;
        }
        else
        {
            customers[customer_ID].waited_time += 1;
        }

        if (customers[customer_ID].waited_time == AGE_UNIT)
        {
            customers[customer_ID].waited_time = 0;
            customers[customer_ID].age += 1;
        }

        if (customers[customer_ID].age == 17)
        {
            Enqueue_queue_1(queue_1, customers, customer_ID);
            Remove_element(customers, queue_3, customer_ID);
        }

    }
    
}

// process command line arguments
// https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Provide input and output file names." << std::endl;
        return -1;
    }  

    //std::ifstream in_file("C:\\University Stuff\\Operating System\\data_1111.txt");
    //std::ofstream out_file("C:\\University Stuff\\Operating System\\data_1111.txt_test");

    std::ifstream in_file(argv[1]);
    std::ofstream out_file(argv[2]);

    if ((!in_file) || (!out_file))
    {
        std::cerr << "Cannot open one of the files." << std::endl;
        return -1;
    }

    // deque: https://www.geeksforgeeks.org/deque-cpp-stl/
    // vector: https://www.geeksforgeeks.org/vector-in-cpp-stl/
    std::deque<Event> arrival_events; // new customer arrivals
    std::vector<Customer> customers;  // information about each customer

    // read information from file, initialize events queue
    initialize_system(in_file, arrival_events, customers);

    int current_id = -1;     // who is using the machine now, -1 means nobody
    int time_out = -1;       // time when current customer will be preempted
    std::deque<int> queue_0;
    std::deque<int> queue_1; // High priority, SRJF, RR = 5
    std::deque<int> queue_2; // High priority, SRJF, RR = 10
    std::deque<int> queue_3; // FCFS

    // step by step simulation of each time slot
    bool all_done = false;

    for (int current_time = 0; !all_done; current_time++)
    {
        if (!queue_3.empty())
            Aging(customers, queue_1, queue_3); 

        while (!arrival_events.empty() && (current_time == arrival_events[0].event_time))
        {
            Enqueue_queue_0(queue_0, customers, arrival_events[0].customer_id);
            arrival_events.pop_front();
        }

        if (current_id >= 0)
        {
            if (customers[current_id].current_queue == 3)
            {
                if (!queue_0.empty() || !queue_1.empty() || !queue_2.empty())
                {
                    int last_run = current_time - customers[current_id].playing_since;
                    customers[current_id].slots_remaining -= last_run;

                    if (customers[current_id].slots_remaining > 0)
                    {
                        customers[current_id].quantum_done = last_run;
                        Enqueue_queue_3(queue_3, customers, current_id);
                    }

                    time_out = -1;
                    current_id = -1;
                }
            }
            else if (customers[current_id].current_queue == 2)
            {
                if (!queue_0.empty() || !queue_1.empty())
                {
                    int last_run = current_time - customers[current_id].playing_since;
                    customers[current_id].slots_remaining -= last_run;

                    if (customers[current_id].slots_remaining > 0)
                    {
                        customers[current_id].quantum_done = last_run;
                        Enqueue_queue_2(queue_2, customers, current_id);
                    }

                    time_out = -1;
                    current_id = -1;
                }
            }

            else if (customers[current_id].current_queue == 1)
            {
                if (!queue_0.empty())
                {
                    int last_run = current_time - customers[current_id].playing_since;
                    customers[current_id].slots_remaining -= last_run;

                    if (customers[current_id].slots_remaining > 0)
                    {
                        customers[current_id].quantum_done = last_run;
                        Enqueue_queue_1(queue_1, customers, current_id);
                    }

                    time_out = -1;
                    current_id = -1;
                }
            }

            if (current_time == time_out)
            {
                int last_run = current_time - customers[current_id].playing_since;
                customers[current_id].slots_remaining -= last_run;

                if (customers[current_id].current_queue == 0 && customers[current_id].slots_remaining > 0)
                {
                    if (customers[current_id].priority == 1)
                        Enqueue_queue_3(queue_3, customers, current_id);
                    else
                        Enqueue_queue_1(queue_1, customers, current_id);
                }
                else if (customers[current_id].current_queue == 1 && customers[current_id].slots_remaining > 0)
                {
                    Enqueue_queue_2(queue_2, customers, current_id);
                }
                else if (customers[current_id].current_queue == 2 && customers[current_id].slots_remaining > 0)
                {
                    Enqueue_queue_3(queue_3, customers, current_id);
                }

                current_id = -1; // the machine is free now
            }
        }
        // if machine is empty, schedule a new customer
        if (current_id == -1)
        {
            if (!queue_0.empty()) // is anyone waiting?
            {
                current_id = queue_0.front();
                queue_0.pop_front();
                if (QUANTUM_0 > customers[current_id].slots_remaining)
                    time_out = current_time + customers[current_id].slots_remaining;
                else
                    time_out = current_time + QUANTUM_0;

                customers[current_id].playing_since = current_time;
            }
            else if (!queue_1.empty()) // is anyone waiting?
            {
                current_id = queue_1.front();
                queue_1.pop_front();
                if (customers[current_id].quantum_done != -1)
                {
                    int quantum_remain = QUANTUM_1 - customers[current_id].quantum_done;
                    if (quantum_remain > customers[current_id].slots_remaining)
                        time_out = current_time + customers[current_id].slots_remaining;
                    else
                        time_out = current_time + quantum_remain;
                }
                else
                {
                    if (QUANTUM_1 > customers[current_id].slots_remaining)
                    {
                        time_out = current_time + customers[current_id].slots_remaining;
                    }
                    else
                    {
                        time_out = current_time + QUANTUM_1;
                    }
                    customers[current_id].playing_since = current_time;
                }
            }

            else if (!queue_2.empty()) // is anyone waiting?
            {
                current_id = queue_2.front();
                queue_2.pop_front();

                if (customers[current_id].quantum_done != -1)
                {
                    int quantum_remain = QUANTUM_2 - customers[current_id].quantum_done;
                    if (quantum_remain > customers[current_id].slots_remaining)
                        time_out = current_time + customers[current_id].slots_remaining;
                    else
                        time_out = current_time + quantum_remain;
                }
                else
                {
                    if (QUANTUM_2 > customers[current_id].slots_remaining)
                    {
                        time_out = current_time + customers[current_id].slots_remaining;
                    }
                    else
                    {
                        time_out = current_time + QUANTUM_1;
                    }
                    customers[current_id].playing_since = current_time;
                }

                customers[current_id].playing_since = current_time;
            }

            else if (!queue_3.empty()) // is anyone waiting?
            {
                current_id = queue_3.front();
                queue_3.pop_front();

                time_out = current_time + customers[current_id].slots_remaining;

                customers[current_id].playing_since = current_time;
            }
        }

        print_state(out_file, current_time, current_id, arrival_events, queue_3);
        all_done = (arrival_events.empty() && queue_1.empty() && queue_2.empty() && queue_3.empty() && (current_id == -1));
    }
    return 0;
}
