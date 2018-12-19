#undef DEBUG

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <queue>
using namespace std;

condition_variable cond_var;
mutex m;

int main() {
	int c = 0;
	bool notified = false;
	bool done = false;
	queue<int> goods;

	thread producer([&]() {

		for (int i = 0; i < 500; ++i) {
			lock_guard<mutex> lk(m); // begin critical region

			goods.push(i);
			c++;
#ifdef DEBUG
			cout << "Producer: notifying with c == " << c << ", i == " << i << endl;
#endif
			notified = true;
			cond_var.notify_one();

			// end critical region (lk goes out of scope)
		}

		m.lock();
#ifdef DEBUG	
		cout << "Producer: Done!\n";
#endif
		done = true;
		m.unlock();
	});

	thread consumer([&]() {

		do {
			unique_lock<mutex> lock(m); // begin critical region
			while (!notified) {
				cond_var.wait(lock);
			}
#ifdef DEBUG
			cout << "Consumer: notified with c == " << c << endl;
#endif
			while (!goods.empty()) {
				goods.pop();
				c--;
			}

			if (done) {
#ifdef DEBUG
				cout << "Consumer: Done!\n";
#endif
				lock.unlock();
				break;
			}

			lock.unlock(); // end critical region
		} while (true);
	});

	producer.join();
	consumer.join();

	// Net should be 0 if goods.push() and goods.pop() have
	// correct mutual exclusion
	cout << "Net: " << c << endl;
}
