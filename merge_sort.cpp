#include "merge_sort.h"
#include <iostream>
#include <vector>
#include <random>     
#include <algorithm>  
#include <numeric>

using namespace std;
using namespace _merge_sort;

//向外暴露给用户使用的，参数较少
void _merge_sort::merge_sort(int*arr,int n) {
	//进行简单的非空以及以及元素数量判断（只有一个不用再排序，默认有序）
	if (!arr || n <= 1) return;
    //这里调用真正的归并排序——注意：如果你测试不同版本归并排序，把下面函数名以及参数改一下
    final_merge(arr,n);
}

//基本归并排序——递归
//参数：arr数组，i为起始位置，j为终点
void _merge_sort::merge_base_recursion(int* arr, int i, int j) {
    //递归终止条件：当数组被划分为单元素数组时候递归终止（或非法条件i>j）
    if (i >= j)return;
    //这里确定从中间进行划分——注意：为了防止溢出，尽量不要使用(i+j)/2或者(i+j)>>1
    int mid = i+((j-i)>>1);
    merge_base_recursion(arr, i, mid);               //左子数组采用相同操作，继续划分
    merge_base_recursion(arr, mid + 1, j);           //右子数组采用相同操作，继续划分 

    //到这里就已经形成两个有序数组，进行合并
    int* tp = new int[j - i + 1];                         //创建临时数组
    int l1 = i, r1 = mid, l2 = mid + 1, r2 = j, index = 0;     //创建一系列指针指向左右数组的边界[l1,r1],[l2,r2]，index表示要插入tp哪个位置                                      

    /*
    * l1,l2初始指向两个数组起点，只要两个指针都没超过终点，就继续遍历
    * 博主为了简洁：写成一段代码：比较l1,l2处元素大小，把更小的元素放进index位置，然后index++，同时让更小的指针++
    */
    while (l1 <= r1 && l2 <= r2) tp[index++] = arr[l1] <= arr[l2] ? arr[l1++] : arr[l2++];    

    //下面两个循环，判断如果左右其中一个数组有剩余元素，则继续放进tp中
    while (l1 <= r1)tp[index++] = arr[l1++];
    while (l2 <= r2) tp[index++] = arr[l2++];
    while (index--) arr[j--] = tp[index]; //将tp数组元素拷贝到[i,j]区间，我这里采用从右往左拷贝，用tp的index值覆盖j处值，然后j--，循环中index--
    delete[] tp;                                       //别忘了释放tp
}



//插入排序(博主后面也会出一期)
void _merge_sort::insert_sort(int*arr,int m,int n) {
    if (m >= n)return;
    for (int i = m+1; i <= n; ++i) { //默认起始元素已序，从已序元素中插入一个新的
        int tp = arr[i];    //目标元素存一下，不然可能被覆盖
        int pointer = i-1;  //移动的指针，找到要插入位置（注意稳定性！！！：往左查找时候遇到相同的元素，一定要插到相同元素后面,循环条件用 > ）
        while (pointer >= m && arr[pointer] > tp) {
            arr[pointer + 1] = arr[pointer];  //比tp大值往右移动，腾位置
            --pointer;    
        }
        //结束后，pointer位置元素等于或者小于目标元素，在后面进行插入
        arr[pointer + 1] = tp;
    }
}

//优化后归并排序——递归
void _merge_sort::final_merge_recursion(int* arr, int i, int j,int*tp) {           //优化一：创建全局的tp，存放排序后的位置，减少内存频繁创建开销
    //递归终止条件：当数组被划分为单元素数组时候递归终止（或非法条件i>j）
    if (i >= j)return;

    /*
    * 我们可以设置一个阈值，当数组元素小于等于一定范围时候，引入其他适合小规模的排序算法（插入，冒泡，选择），减少递归调用的系统开销
    * 这里我设置一个阈值为10，小于等于10采用插入排序
    */
    if (j - i + 1 <= 10) {
        insert_sort(arr,i,j);
        return;
    }

    //这里确定从中间进行划分
    int mid = i + ((j - i) >> 1);
    final_merge_recursion(arr, i, mid,tp);               //左子数组采用相同操作，继续划分，优化一：共用同一个tp
    final_merge_recursion(arr, mid + 1, j,tp);           //右子数组采用相同操作，继续划分 ，优化一：共用同一个tp

 
    //优化三：不要先进行合并，如果已经完全有序，则直接退出（左数组最后一个元素<=右边数组第一个元素）
    if (arr[mid] <= arr[mid + 1]) return;

    int l1 = i, r1 = mid, l2 = mid + 1, r2 = j, index = 0;     //创建一系列指针指向左右数组的边界[l1,r1],[l2,r2]，index表示要插入tp哪个位置                                      
    /*
    * l1,l2初始指向两个数组起点，只要两个指针都没超过终点，就继续遍历
    * 博主为了简洁：写成一段代码：比较l1,l2处元素大小，把更小的元素放进index位置，然后index++，同时让更小的指针++
    */
    while (l1 <= r1 && l2 <= r2) tp[index++] = arr[l1] <= arr[l2] ? arr[l1++] : arr[l2++];

    //下面两个循环，判断如果左右其中一个数组有剩余元素，则继续放进tp中
    while (l1 <= r1)tp[index++] = arr[l1++];
    while (l2 <= r2) tp[index++] = arr[l2++];
    while (index--) arr[j--] = tp[index]; //将tp数组元素拷贝到[i,j]区间，我这里采用从右往左拷贝，用tp的index值覆盖j处值，然后j--，循环中index--
}



//基本的归并排序实现——非递归
void _merge_sort::merge_base(int* arr,int n) {
    //简单的判空条件
    if (!arr || n <= 1) return;
    /*
    * 我们假设数组已经被划分成长度为1的有序子数组
    * 对长度为1子数组进行合并
    * 然后长度就变成2，以此循环，长度变成4，8.......
    */
    for (int len = 1; len < n; len *= 2) {  //对长度遍历，每个长度都会进行合并，然后更新len，变成原来2倍
        /*
        * 我们要从左向右合并长度为len的子数组，那么我们要遍历的所有区间的长度应该为2*len
        * 举例子：{5，4，3，2，1，6，7，8，9} 当len=1时候
        * 内部遍历的区间依次{5,4}{3,2}{1,6}{7,8},{9}，在每个区间找到mid，和右边界right，进行合并
        * 比如说{5,4}这个区间，left指向元素5，mid指向元素5，right指向元素为4，然后合并就行
        */
        for (int left = 0; left <= n - 1; left += len * 2) {
            int mid = min(left + len-1,n-1);   //找到mid，要注意不要超出数组范围
            int right = min(left + len * 2 - 1,n-1); //left+len*2是下一个区间的开始，减去1为该区间最后一个元素，注意不要超出数组范围
            //找到left,mid,right后就可以进行合并了，不过要和递归一下，先判断一下区间[left,right]合法,不合法直接跳过
            if (left >= right) continue;
            //合并算法：和递归中合并算法一样

            int* tp = new int[right - left + 1];                         //创建临时数组
            int l1 = left, r1 = mid, l2 = mid + 1, r2 = right, index = 0;     //创建一系列指针指向左右数组的边界[l1,r1],[l2,r2]，index表示要插入tp哪个位置                                      

            /*
            * l1,l2初始指向两个数组起点，只要两个指针都没超过终点，就继续遍历
            * 博主为了简洁：写成一段代码：比较l1,l2处元素大小，把更小的元素放进index位置，然后index++，同时让更小的指针++
            */
            while (l1 <= r1 && l2 <= r2) tp[index++] = arr[l1] <= arr[l2] ? arr[l1++] : arr[l2++];

            //下面两个循环，判断如果左右其中一个数组有剩余元素，则继续放进tp中
            while (l1 <= r1)tp[index++] = arr[l1++];
            while (l2 <= r2) tp[index++] = arr[l2++];
            while (index--) arr[right--] = tp[index]; //将tp数组元素拷贝到[i,j]区间，我这里采用从右往左拷贝，用tp的index值覆盖j处值，然后j--，循环中index--
            delete[] tp;                                       //别忘了释放tp
        }
    }
}



//基本的归并排序实现——非递归
void _merge_sort::final_merge(int* arr, int n) {
    //简单的判空条件
    if (!arr || n <= 1) return;

    //优化二：预排序块策略：先设置一个阈值，把数组划分长度为阈值的小区间，在小区间使用小规模排序算法（插入、选择、冒泡等）
    int threshold = 10;  //这里我设置阈值为10
    for (int left = 0; left <= n - 1; left += threshold) {
        int right = min(left+threshold-1,n-1);   //找到right，不能越界
        insert_sort(arr,left,right);
     }
    //优化一：在循环外部创建tp数组，减少系统开销
    int* tp = new int[n];                         //创建临时数组
    /*
    * 我们假设数组已经被划分成长度为threshold的有序子数组
    * 对长度为threshold子数组进行合并
    * 然后长度就变成2*threshold，每次循环*2
    */
    for (int len = threshold; len < n; len *= 2) {  //对长度遍历，每个长度都会进行合并，然后更新len，变成原来2倍
       
        //我们要从左向右合并长度为len的子数组，那么我们要遍历的所有区间的长度应该为2*len
        for (int left = 0; left <= n - 1; left += len * 2) {
            int mid = min(left + len - 1, n - 1);   //找到mid，要注意不要超出数组范围
            int right = min(left + len * 2 - 1, n - 1); //left+len*2是下一个区间的开始，减去1为该区间最后一个元素，注意不要超出数组范围
            //合并算法：
            //找到left,mid,right后就可以进行合并了，不过要和递归一下，先判断一下区间[left,right]合法,不合法直接跳过
            if (left >= right) continue;
            //优化三：已序跳过合并
            if (arr[mid] <= arr[mid + 1])  continue;

            int l1 = left, r1 = mid, l2 = mid + 1, r2 = right, index = 0;     //创建一系列指针指向左右数组的边界[l1,r1],[l2,r2]，index表示要插入tp哪个位置                                      

            /*
            * l1,l2初始指向两个数组起点，只要两个指针都没超过终点，就继续遍历
            * 博主为了简洁：写成一段代码：比较l1,l2处元素大小，把更小的元素放进index位置，然后index++，同时让更小的指针++
            */
            while (l1 <= r1 && l2 <= r2) tp[index++] = arr[l1] <= arr[l2] ? arr[l1++] : arr[l2++];
            //下面两个循环，判断如果左右其中一个数组有剩余元素，则继续放进tp中
            while (l1 <= r1)tp[index++] = arr[l1++];
            while (l2 <= r2) tp[index++] = arr[l2++];
            while (index--) arr[right--] = tp[index]; //将tp数组元素拷贝到[i,j]区间，我这里采用从右往左拷贝，用tp的index值覆盖j处值，然后j--，循环中index--
        }
    }
    delete[] tp;                                       //别忘了释放tp
}





void _merge_sort::test_merge_sort() {
    using namespace std;
    using namespace _merge_sort; 

    cout << "--- 归并排序测试 ---" << endl;


    {
        cout << "\n测试 1: 随机数组" << endl;
        const int N1 = 25;
        vector<int> data1(N1);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000);
        for (int& val : data1) val = dis(gen);

        cout << "排序前: ";
        for (int val : data1) cout << val << " ";
        cout << endl;

        merge_sort(data1.data(), data1.size()); // .data() gets pointer to underlying array

        cout << "排序后: ";
        for (int val : data1) cout << val << " ";
        cout << endl;
        cout << "是否已排序: " << (std::is_sorted(data1.begin(), data1.end()) ? "是" : "否") << endl;
    }

    {
        cout << "\n测试 2: 已排序数组" << endl;
        const int N2 = 20;
        vector<int> data2(N2);
        std::iota(data2.begin(), data2.end(), 1); // Fill with 1, 2, ..., N2

        cout << "排序前: ";
        for (int val : data2) cout << val << " ";
        cout << endl;

        merge_sort(data2.data(), data2.size());

        cout << "排序后: ";
        for (int val : data2) cout << val << " ";
        cout << endl;
        cout << "是否已排序: " << (std::is_sorted(data2.begin(), data2.end()) ? "是" : "否") << endl;
    }

    {
        cout << "\n测试 3: 逆序数组" << endl;
        const int N3 = 15;
        vector<int> data3(N3);
        std::iota(data3.rbegin(), data3.rend(), 1); // Fill with N3, ..., 2, 1

        cout << "排序前: ";
        for (int val : data3) cout << val << " ";
        cout << endl;

        merge_sort(data3.data(), data3.size());

        cout << "排序后: ";
        for (int val : data3) cout << val << " ";
        cout << endl;
        cout << "是否已排序: " << (std::is_sorted(data3.begin(), data3.end()) ? "是" : "否") << endl;
    }


    {
        cout << "\n测试 4: 包含重复元素的数组" << endl;
        vector<int> data4 = { 5, 2, 8, 2, 9, 1, 5, 4, 2, 7, 3, 5 };

        cout << "排序前: ";
        for (int val : data4) cout << val << " ";
        cout << endl;

        merge_sort(data4.data(), data4.size());

        cout << "排序后: ";
        for (int val : data4) cout << val << " ";
        cout << endl;
        cout << "是否已排序: " << (std::is_sorted(data4.begin(), data4.end()) ? "是" : "否") << endl;
    }


    {
        cout << "\n测试 5: 小数组 " << endl;
        vector<int> data5 = { 4, 1, 3, 2 }; // Size 4 < 16

        cout << "排序前: ";
        for (int val : data5) cout << val << " ";
        cout << endl;

        merge_sort(data5.data(), data5.size());

        cout << "排序后: ";
        for (int val : data5) cout << val << " ";
        cout << endl;
        cout << "是否已排序: " << (std::is_sorted(data5.begin(), data5.end()) ? "是" : "否") << endl;
    }
    {
        cout << "\n测试 6: 单元素数组" << endl;
        vector<int> data6 = { 42 };

        cout << "排序前: ";
        for (int val : data6) cout << val << " ";
        cout << endl;

        merge_sort(data6.data(), data6.size());

        cout << "排序后: ";
        for (int val : data6) cout << val << " ";
        cout << endl;
        cout << "是否已排序: " << (std::is_sorted(data6.begin(), data6.end()) ? "是" : "否") << endl;
    }

    {
        cout << "\n测试 7: 空数组" << endl;
        vector<int> data7 = {};

        cout << "排序前: (空)" << endl;
        merge_sort(data7.data(), data7.size()); // Should handle gracefully
        cout << "排序后: (空)" << endl;
        cout << "是否已排序: " << (std::is_sorted(data7.begin(), data7.end()) ? "是" : "否") << endl;
    }

    {
        cout << "\n测试 8: 空指针" << endl;
        int* null_ptr = nullptr;
        cout << "对空指针排序..." << endl;
        merge_sort(null_ptr, 5); // Should handle gracefully without crashing
        cout << "空指针测试完成 (未崩溃即视为通过)" << endl;
    }

    cout << "\n--- 所有测试完成 ---" << endl;
}