#ifndef VECTOR_H_
#define VECTOR_H_

namespace components {
	template <class Ty>
	class Vector {
	public:
		typedef unsigned Size;
		#define ScaleFactor 1.75;

		Vector(Size initialCpacity = 5) {
			firstElement = afterLastElement = new Ty[initialCpacity];
			capacity = initialCpacity;
		}

		void push(Ty& item) {
			if (size() == capacity) {
				resize();
			}
			*afterLastElement = item;
			afterLastElement++;
		}

		void push(Ty&& item) {
			if (size() == capacity) {
				resize();
			}
			*afterLastElement = item;
			afterLastElement++;
		}

		Ty pop() {
			//if(empty()) throw "Vector is empty, cant pop()";
			auto retVal = *(afterLastElement - 1);
			afterLastElement -= 1;
			return retVal;
		}

		Ty& get(Size index) {
			//if(index < size()) throw "Vector index is bad, probably not less than size()";
			return *(firstElement + index);
		}
		Size size() {
			return afterLastElement - firstElement;
		}

		bool empty() {
			return size() == 0;
		}

		~Vector() {
			dispose();
		}
	private:
		Ty* firstElement;
		Ty* afterLastElement;
		Size capacity;

		void resize() {
			Size newCapacity = capacity * ScaleFactor;
			Ty *newFirst, *newAfterLast;
			newFirst = newAfterLast = new Ty[newCapacity];

			for (Size i = 0; i < capacity; i++) {
				*newAfterLast = get(i);
				++newAfterLast;
			}

			dispose();

			capacity = newCapacity;
			firstElement = newFirst;
			afterLastElement = newAfterLast;
		}

		void dispose() {
			delete[] firstElement;
		}
	};
};

#endif