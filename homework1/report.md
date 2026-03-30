
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
| $35, 10, 70, 5, 25$ | $5,10,25,35,70$ | $5,10,25,35,70$       |


### 結論

1. 程式成功透過堆疊調整演算法維持最小優先權特性。
2. 利用 $template <class T>$ 可支援各種資料型態。

## 申論及開發報告

1. **函式特性**  
$Ackermann$ 函數的成長極快，超過一定值（如 m ≥ 4, n ≥ 2）會導致遞迴過深而異位。

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
作業二 Binary Search Tree

## 解題說明

本題要求實作二元搜尋樹，並測量隨機插入下樹的高度變化，同時實現節點刪除功能。

### 解題策略
1.隨機數實驗：利用 $mt19937$ 產生均勻隨機數，建立不同規模的 $BST$ 並測量高度。
2.高度驗證：計算 $Height / \log_2 n$ 之比例，觀察是否如理論預期趨近於常數 $2$ 。
## 程式實作

以下為主要程式碼：

```#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
//定義二元搜尋樹節點
struct Node
{
    int data;
    Node* left, * right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};
//尋找最小值節點
Node* findmin(Node* root)
{
    while (root && root->left != nullptr) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int k)
{
    if (root == nullptr) return root;
    // 尋找要刪除的目標
    if (k < root->data)
        root->left = deleteNode(root->left, k);
    else if (k > root->data)
        root->right = deleteNode(root->right, k);
    else {
        //只有一個子節點 沒有子節點
        if (root->left == nullptr)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        //有兩個子節點
        //找到右子樹中最小的節點來接替
        Node* temp = findmin(root->right);
        root->data = temp->data; //複製
        root->right = deleteNode(root->right, temp->data);//刪除原本的最小節點
    }
    return root;
}
// 插入節點
Node* insert(Node* root, int val)
{
    if (root == nullptr) return new Node(val);
    if (val < root->data) root->left = insert(root->left, val);
    else if (val > root->data) root->right = insert(root->right, val);
    return root;
}
// 計算樹的高度
int TreeH(Node* root)
{
    if (root == nullptr) return -1;
    return 1 + max(TreeH(root->left), TreeH(root->right));
}
//釋放記憶體
void deleteT(Node* root)
{
    if (root == nullptr) return;
    deleteT(root->left);
    deleteT(root->right);
    delete(root);
}
//中序走訪
void inorder(Node* root)
{
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}
int main() {
    vector<int> n = { 100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000 };
    random_device rd;//隨機數產生器
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000000); //隨機數範圍
    cout << fixed << setprecision(4);
    cout << "n\t\tHeight\t\tlog2(n)\t\t(Height/log2n)" << endl;//格式n Height log2(n) (Height/log2n)
    cout << "------------------------------------------------------------" << endl;
    for (int a : n)
    {
        Node* root = nullptr;
        for (int i = 0; i < a; ++i) root = insert(root, dis(gen));
        int h = TreeH(root);
        double ratio = h / log2(a);
        cout << a << "\t\t" << h << "\t\t" << log2(a) << "\t\t" << ratio << endl;
        deleteT(root);
    }
    //測試(b)功能
    cout << endl << "Part (b)" << endl;
    Node* testRoot = nullptr;
    vector<int> testData = { 30, 75, 60, 40, 25, 65, 80 };
    cout << "插入數據: ";
    for (int x : testData)
    {
        cout << x << " ";
        testRoot = insert(testRoot, x);
    }
    int target = 30;//測試刪除節點
    testRoot = deleteNode(testRoot, target);
    cout << "\n刪除後:";
    inorder(testRoot);
    cout << endl;
    deleteT(testRoot);
    return 0;
}
```

## 效能分析

1. 時間複雜度：
隨機插入的平均時間: $O(\log n)$。
計算高度: $O(n)$。
2. 空間複雜度： $O(n)$

## 測試與驗證

### 測試案例
<img width="477" height="285" alt="image" src="https://github.com/user-attachments/assets/f9f005ec-6669-494c-bcb3-ecec7e8d74c7" />

測試一: 
輸入: $100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000$

輸出:<img width="592" height="280" alt="image" src="https://github.com/user-attachments/assets/3c788e90-baaa-4906-9c5f-22af25e3b5ca" />

測試二:
輸入: $30, 75, 60, 40, 25, 65, 80$

輸出: $25,40,60,65,75,80$

### 結論

1. 程式能正確排列出元素的冪集合。  
2. 在有相同元素時不會出現重複的答案。 

## 申論及開發報告

1. **選擇遞迴的原因**

遞迴能以簡潔的方式展現所有組合，程式結構清楚，邏輯自然。

2. **動態記憶體配置**  

因為剛開始需要輸入元素的個數所以使用動態記憶體配置以節省空間
