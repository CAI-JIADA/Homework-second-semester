
# 41343145

作業一 Max/Min Heap

## 解題說明

本題要求實作一個最小優先權佇列，利用最小堆疊的結構來達成高效的資料存取。

### 解題策略

1. 定義抽象類別：建立 $MinPQ$ 模板抽象類別，定義 $Push、Pop、Top$ 函式。
2. 繼承與實作：建立 $MinHeap$ 類別繼承 $MinPQ$ ，並使用 $std::vector$ 作為底層儲存結構以實現動態擴充。 
3. 插入(Push)：將元素置於末尾後執行確保父節點永遠小於等於子節點。
4. 刪除 (Pop)：將根節點與末尾元素交換後移除，再執行向下調整修復堆疊結構。

## 程式實作

以下為主要程式碼：

```#include <iostream>
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
```

## 效能分析

1. 時間複雜度：
Push： $O(\log n)$ 
Pop： $O(\log n)$ 
Top： $O(1)$ 
2. 空間複雜度： $O(n)$

## 測試與驗證

### 測試案例

|輸入參數 $m$ $n$ | 預期輸出 | 實際輸出 |
|---------------|----------|----------|
| $35, 10, 70, 5, 25$ | $5 10 25 35 70$        | $5 10 25 35 70$       |


### 結論

1. 程式能正確計算 $Ackermann(m, n)$ 的答案。
2. $Ackermann$ 函數成長數度極快以至於過大數字程式無法處理。  

## 申論及開發報告

1. **為何使用遞迴**
   
除了題目本身需求外 $Ackermann$ 函數的定義本身是遞迴形式，因此以遞迴程式最直觀。 

2. **函式特性**  
$Ackermann$ 函數的成長極快，超過一定值（如 m ≥ 4, n ≥ 2）會導致遞迴過深而異位。

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
作業二

## 解題說明

本題要求使用遞迴方式列出所有可能的子集合。

### 解題策略
使用一個 char 陣列 S[] 儲存輸入的集合元素。
使用另一個 char 陣列 subset[] 暫存目前遞迴過程中產生的子集合。
為了讓重複的元素相鄰，先用```sort(S, S + n)```排序，若在遞迴中若發現連續相同元素，利用```if (i > index && S[i] == S[i - 1]) continue;```跳過重複組合。
## 程式實作

以下為主要程式碼：

```#include<iostream>
#include <algorithm>//排序用
using namespace std;
void powerset(char S[], int n, int index, char subset[], int subsetSize) {//index指目前遞迴到第幾個元素，subsetSize表示目前子集合中有多少元素
    // 輸出目前子集合
    cout << "(";
    for (int i = 0; i < subsetSize; i++) {
        cout << subset[i];
    }
    cout << ")" << endl;
    for (int i = index; i < n; i++) {//如果有重複元素跳過
        if (i > index && S[i] == S[i - 1])continue;
        subset[subsetSize] = S[i];
        powerset(S, n, i + 1, subset, subsetSize + 1);
    }
}
int main() {
	int n;
	cout << "請輸入n:";
	cin >> n;
	cout << endl<< "請輸入元素:";
	char* S = new char[n];//建立集合陣列
    char* subset = new char[n];//暫存目前正在生成的子集合
	for (int i = 0;i < n;i++) {
		cin >> S[i];
	}
    sort(S, S + n);//將重複元素排一起
	cout << endl<< "冪集合為：" ;
    powerset(S, n, 0, subset, 0);
    delete[] S;
    delete[] subset;
	return 0;
}
```

## 效能分析

1. 時間複雜度：程式的時間複雜度為 $O(n*2^n)$。
2. 空間複雜度：空間複雜度為 $O(n)$。

## 測試與驗證

### 測試案例

測試一: $n = 3$  $abc$
輸出:()(a)(ab)(abc)(ac)(b)(bc)(c)

測試二: $n = 3$  $abb$
輸出:()(a)(ab)(abb)(b)(bb)

### 結論

1. 程式能正確排列出元素的冪集合。  
2. 在有相同元素時不會出現重複的答案。 

## 申論及開發報告

1. **選擇遞迴的原因**

遞迴能以簡潔的方式展現所有組合，程式結構清楚，邏輯自然。

2. **動態記憶體配置**  

因為剛開始需要輸入元素的個數所以使用動態記憶體配置以節省空間
