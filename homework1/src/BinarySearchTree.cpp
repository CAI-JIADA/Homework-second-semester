#include <iostream>
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