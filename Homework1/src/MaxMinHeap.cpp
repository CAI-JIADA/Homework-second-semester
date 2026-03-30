#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;
template <class T>
class MinPQ 
{
public:
    virtual ~MinPQ() {}//虛擬解構子
    virtual bool IsEmpty() const = 0;//是否為空
    virtual const T& Top() const = 0;//回傳最小值
    virtual void Push(const T& x) = 0;//插入元素
    virtual void Pop() = 0;//刪除最小值
};
template <class T>
class MinHeap : public MinPQ<T> 
{
private:
    vector<T> heap;
    //向上調整SiftUp用於Push
    void siftUp(int index) 
    {
        while (index > 0) 
        {
            int parent = (index - 1) / 2;
            if (heap[index] < heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent;
            }
            else break;
        }
    }
    //向下調整Sift Down用於Pop
    void siftDown(int index)
    {
        int size = heap.size();
        while (true) 
        {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;
            if (left < size && heap[left] < heap[smallest]) smallest = left;
            if (right < size && heap[right] < heap[smallest]) smallest = right;
            if (smallest != index) 
            {
                swap(heap[index], heap[smallest]);
                index = smallest;
            }
            else break;
        }
    }
public:
    bool IsEmpty() const override 
    {
        return heap.empty();
    }
    const T& Top() const override 
    {
        if (IsEmpty()) throw runtime_error("Queue is empty");
        return heap[0];
    }
    void Push(const T& x) override 
    {
        heap.push_back(x);
        siftUp(heap.size() - 1);
    }
    void Pop() override 
    {
        if (IsEmpty()) throw runtime_error("Queue is empty");
        heap[0] = heap.back();//用最後一個元素覆蓋根節點
        heap.pop_back();
        if (!heap.empty()) siftDown(0);
    }
};
int main() {
    MinHeap<int> minHeap;
    cout << "插入數據: 35, 10, 70, 5, 25" << endl;
    minHeap.Push(35);
    minHeap.Push(10);
    minHeap.Push(70);
    minHeap.Push(5);
    minHeap.Push(25);
    cout << "依序取出最小值: ";
    while (!minHeap.IsEmpty()) 
    {
        cout << minHeap.Top() << " ";
        minHeap.Pop();
    }
    cout << endl;
    return 0;
}