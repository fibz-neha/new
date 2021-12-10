#include<iostream>

using namespace std;

bool locked = false;
int holder;

bool check_lock_release() {
    char choice;
    cout << "Is the release message received for the data object from T" << holder << ": ";
    cin >> choice;
    if(choice == 'y') {
        locked = false;
        cout << "Lock Released by T"<< holder << ".\n";
        return true;
    }
    return false;
}

void get_lock(int transaction) {
    char choice;
    locked = true;
    choice = 'n';
    cout << "Lock granted to T" << transaction << ".\n";
    holder = transaction;
}


int main() {
    char choice, next = 'n';
    int iter = 1;
    do {
        cout << "If Transiction T" << iter << " wants to lock the data object (y/n): ";
        cin >> choice;
        if(choice == 'y' && !locked) {
            get_lock(iter);
        } 
        else if(locked) {
            if(check_lock_release()) {
                get_lock(iter);
            }
            else 
                cout << "Data object is locked \n";
        }
        else {
            check_lock_release();
        }
        cout << "Continue to the next iteration (y/n): ";
        cin >> next;
        iter++;
    } while(next == 'y');
}
