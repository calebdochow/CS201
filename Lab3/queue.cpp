#include <iostream>
using namespace std;

template <typename T>
class queue{
    private:
        T* array;
        size_t capacity;
        size_t size;
        size_t front;
    public:
        queue() : capacity(10), size(0), front(0){ //Constructor
            array = new T[capacity];
        }

        queue(size_t s) : capacity(s), size(0), front(0){ //Constructor
            array = new T[s];
        }

        ~queue(){ //Deconstructor
            delete[] array;
        }

        void enqueue(T x){ //insert item to end of queue
            array[(front + size++) % capacity] = x;
        }

        T dequeue(){ //remove first item and shift items in queue
            size_t pp = front;
            front = (front + 1) % capacity;
            size--;
            return array[pp];
        }

        queue(const queue & old){ //Copy Constructor
            array = old.array;
            size = old.size;
            capacity = old.capacity;
        }

        queue& operator=(const queue& rhs){//copy assignment operator
            if (this != &rhs) {
                delete[] array;

                capacity = rhs.capacity;
                size = rhs.size;

                array = new T[capacity];
                for (size_t i = 0; i < size; i++) {
                    array[i] = rhs.array[i];
                }
            }
            return *this;
        }

};

int main(){
    queue<int> Q, R;

    for(int i=0;i<10;i++)Q.enqueue(i);

    R = Q;

    cout << Q.dequeue() << endl;
    
    Q.enqueue(500);
    
    for(int i = 0; i < 9; i++) Q.dequeue();
    
    cout << Q.dequeue() << endl;
    
    for(int i = 0; i < 9; i++) cout << R.dequeue() << endl;

    return 0;
}