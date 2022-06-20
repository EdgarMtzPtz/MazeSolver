
#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

// NOTE: You may not include any other libraries!
#include <unordered_map>
#include <vector>
#include <utility> // Has pair and swap
//#include <queue>

using namespace std;

template <typename T>
class MinPriorityQueue
{
	// For the mandatory running times below:
	//
	// n is the number of elements in the MinPriorityQueue.
	//
	// Assume that the operations of unordered_map are O(1) time 
	// (they are average case, but not worst-case).

	public:
		// Creates an empty MinPriorityQueue
		MinPriorityQueue()
		{
			// TODO
		}

		// Returns the number of elements in the MinPriorityQueue.
		//
		// Must run in O(1) time.
		int size()
		{
			// TODO
			return H.size();
		}	

		// Pushes a new value x with priority p
		// into the MinPriorityQueue.
		//
		// Must run in O(log(n)) time.		 
		void push(T x, int p)
		{
			// TODO
			H.push_back(make_pair(x, p));
			I[x] = H.size() - 1;
			//I.emplace(x,H.size()-1);
			bubble_up(H.size() - 1);
			
			//needs to be booble
		}

		// Returns the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		// 
		// Must run in O(1) time.
		T front()
		{
			if (H.empty()) {
				return NULL;
			}
			else
			{
				
				return H[0].first;
			}
			// TODO	
		}

		// Removes the value at the front of the MinPriorityQueue.
		// Undefined behavior if the MinPriorityQueue is empty.
		//
		// Must run in O(log(n)) time. 
		void pop()
		{
			// TODO	
			if (H.empty()) {
				//cout << "nothing to pop";
			}
			else if (H.size() == 1) {
				I.erase(H[0].first);
				H.pop_back();
			}
			else
			{
				
					I.erase(H[0].first); //errase from I
					swap(H[0], H[H.size() - 1]);
					H.pop_back();
					
					//rebubbly
					if (H.size() == 1 || H.empty()) {
						//don't do a thing
					}
					else
					bubble_down(0);
				
			}
		}
		void popback() {
			if (H.empty()) {

			}
			else if (H.size() == 1) 
			{
				I.erase(H[0].first);
				H.pop_back();
			}
			else
			{
				I.erase(H[0].first); //errase from I
				//swap(H[0], H[H.size() - 1]);
				H.erase(H.begin());
			}
		}
		// If x is in the MinPriorityQueue 
		// with current priority at least new_p,  
		// then changes the priority of x to new_p.
		// Undefined behavior otherwise.
		//
		// Must run in O(log(n)) time. 
		void decrease_key(T x, int new_p)
		{
			// TODO
			int d = I.at(x);
			//cout << d << endl;
			if (H[d].second > new_p)
			{
			H[d].second = new_p;
			bubble_up(d);
			}
		}
		void test_display()
		{
			cout << endl;
			cout << "enter test dyspplay" << endl;
			cout << endl;
			for (int i = 0; i < H.size(); i++) {
				cout << i << ": "<<H[i].first <<" " << H[i].second << endl;
				/*if (I.find(H[i].first) == I.end())
					cout << "key not found" << endl;
				else
					cout << "it was here" << endl;*/
			}
			cout << endl;
			/*for (int i = 0; i < I.size(); i++)
				cout << i << ": " << I[i].second << endl;*/
			cout << "data matter data" << endl;
			for (auto x : I)
			{
				cout << x.first << " " << x.second << endl;
			}
			cout << "end of datta mapper" << endl;
			cout << "exit test dyaplay " << endl;
			cout << endl;
		}

	private:
		// You don't need any other instance variables,
		// but you can add some if you want to.
		vector< pair<T, int> > H; // The heap.
		unordered_map<T, int> I;  // Maps values to their indices in H.
		void bubble_up(int index)
		{
			while (parent_violation(index))
			{
				I.at(H[index].first) = parent(index);
				I.at(H[parent(index)].first) = index;
				swap(H[index], H[parent(index)]);
				//I.find(H[index].first swap(, I.find(H[parent(index)].first));
				
/*
`				
				auto it = map.find(key)
				if (it != map.end())
					it->second = new_value;
*/
				//auto it = I.find(H[index].first);
				//auto it0 = I.find(H[parentchildren(index)].first);

				//int tmp = it->second; //I.find(H[index].first);
				//int tmp0 = it0->second; //I.find(H[leftchildren(index)].first);

				//it->second = tmp0; //I.find(H[index].first) = tmp0;
				//it0->second = tmp; //I.find(H[leftchildren(index)].first) = tmp;

				index = parent(index);
			}
		}
		void bubble_down(int index)
		{
			//cout << "index: " << index << " H.size()-1: " << H.size() - 1 << endl;
			while (children_violation(index))
			{	
				/*cout << "current index: " << index << " it holds: " << H[index].second << endl;
				if (leftchildren(index) < H.size()-1)
					cout << "# of left children is " << leftchildren(index) << " it holds: " << H[leftchildren(index)].second << endl;
				if (rightchildren(index) < H.size()-1)
					cout << "# of right children is " << rightchildren(index) << " it holds: " << H[rightchildren(index)].second << endl;*/
				//if (((i+1)*2>H.size()|| (i*2)+1>H.size()) {//then there is only one children
				if (rightchildren(index) > H.size()-1) //this means the violation is in the left children
				{
					//cout << "it enter the right children case: " << leftchildren(index) << endl;
					I.at(H[index].first) = leftchildren(index);
					I.at(H[leftchildren(index)].first) = index;
					swap(H[index], H[leftchildren(index)]);
					index = leftchildren(index);
				}
				else {

					if (H[leftchildren(index)].second < H[rightchildren(index)].second) {
						//cout << "left case: " << leftchildren(index) << endl;
						I.at(H[index].first) = leftchildren(index);
						I.at(H[leftchildren(index)].first) = index;
						swap(H[index], H[leftchildren(index)]);

						//auto it = I.find(H[index].first);
						//auto it0 = I.find(H[leftchildren(index)].first);

						//int tmp = it->second; //I.find(H[index].first);
						//int tmp0 = it0->second; //I.find(H[leftchildren(index)].first);

						//it->second = tmp0; //I.find(H[index].first) = tmp0;
						//it0->second = tmp; //I.find(H[leftchildren(index)].first) = tmp;
						//swap(I.find(H[index].first), I.find(H[leftchildren(index)].first));
						index = leftchildren(index);
					}
					else
					{
						//cout << "right case: " << rightchildren(index) << endl;
						I.at(H[index].first) = rightchildren(index);
						I.at(H[rightchildren(index)].first) = index;
						swap(H[index], H[rightchildren(index)]);

						//auto it = I.find(H[index].first);
						//auto it0 = I.find(H[rightchildren(index)].first);

						//int tmp = it->second; //I.find(H[index].first);
						//int tmp0 = it0->second; //I.find(H[leftchildren(index)].first);

						//it->second = tmp0; //I.find(H[index].first) = tmp0;
						//it0->second = tmp; //I.find(H[leftchildren(index)].first) = tmp;

						/*int tmp = I.find(H[index].first);
						int tmp0 = I.find(H[rightchildren(index)].first);
						I.find(H[index].first) = tmp0;
						I.find(H[rightchildren(index)].first) = tmp;*/

						//swap(I.find(H[index].first), I.find(H[rightchildren(index)].first));
						index = rightchildren(index);
					}
				}
			}
		}
		bool parent_violation(int i)
		{
			
			if (H[i].second < H[parent(i)].second)
				return true;
			else
				return false;
		}
		bool children_violation(int i) {
			/*cout << "Enter children violation with i =" << i << " and H.size()=" << H.size() << endl;
			cout << "right children is: " << rightchildren(i) << endl;*/
			if (leftchildren(i) > H.size()-1) //if I is bigger than the size there is no violations
			{
				//cout << "I is bigger than the size there is no violations" << endl;
				return false;
			}
			
			if (rightchildren(i)>H.size()-1) //check if the right doesn't exist 
			{
				//cout << "it enter the second if: ";
				if (H[i].second > H[leftchildren(i)].second) { //left violation
					//cout << " it yield true" << endl;
					return true;
				}
				else {
					//cout << "it yielded false" << endl;
					return false;

				}
				
			}
			if (H[i].second > H[rightchildren(i)].second || H[i].second > H[leftchildren(i)].second) {
				//cout << "enter the third if with true" << endl;
				return true;
			}
			else {
				//cout << "enter the third with false" << endl;
				return false;
			}
		}
		int parent(int i)
		{
			return (i - 1) / 2;
		}
		int rightchildren(int i) {
			//if (i % 2 == 0)// even
			//	return (i * 2) + 1;
			//else //odd
				return (i + 1) * 2;
		}
		int leftchildren(int i) {
			//if (i % 2 == 0)//even
			//	return (i + 1) * 2;
			//else //odd
				return (i * 2) + 1;
		}
};

#endif 

