#include <stdio.h>
#include <string.h>

// 硬币状态：0=真，-1=轻假，1=重假
int coins[8] = { 0,0,0,0,0,0,0,0 };
char names[8] = { 'a','b','c','d','e','f','g','h' };

// 模拟天平称量：返回 1(左>右), 0(左=右), -1(左<右)
int balance(int left[], int left_cnt, int right[], int right_cnt) {
    int sum_left = 0, sum_right = 0;
    for (int i = 0; i < left_cnt; i++) sum_left += coins[left[i]];
    for (int i = 0; i < right_cnt; i++) sum_right += coins[right[i]];
    if (sum_left > sum_right) return 1;
    if (sum_left < sum_right) return -1;
    return 0;
}

// 查找假币
void find_counterfeit() {
    // 第一次称量: abc vs def
    int first_left[] = { 0,1,2 }, first_right[] = { 3,4,5 };
    int res1 = balance(first_left, 3, first_right, 3);
    int fake_idx = -1, fake_type = 0; // -1=轻，1=重

    if (res1 == 0) {
        // 假币在 g/h(6/7)
        int second_left[] = { 6 }, second_right[] = { 0 };
        int res2 = balance(second_left, 1, second_right, 1);
        if (res2 == 1) { fake_idx = 6; fake_type = 1; }
        else if (res2 == -1) { fake_idx = 6; fake_type = -1; }
        else {
            fake_idx = 7;
            int h_left[] = { 7 }, h_right[] = { 0 };
            fake_type = (balance(h_left, 1, h_right, 1) == 1) ? 1 : -1;
        }
    }
    else if (res1 == 1) {
        // abc > def → 第二次称量 ade vs bgh
        int second_left[] = { 0,3,4 }, second_right[] = { 1,6,7 };
        int res2 = balance(second_left, 3, second_right, 3);
        if (res2 == 0) {
            // 假币在 c(2)或f(5)
            int c_left[] = { 2 }, c_right[] = { 0 };
            int res3 = balance(c_left, 1, c_right, 1);
            if (res3 == 1) { fake_idx = 2; fake_type = 1; }
            else { fake_idx = 5; fake_type = -1; }
        }
        else if (res2 == 1) {
            // 假币a(0)重 或 d(3)/e(4)轻
            int d_left[] = { 3 }, d_right[] = { 4 };
            int res3 = balance(d_left, 1, d_right, 1);
            if (res3 == -1) { fake_idx = 3; fake_type = -1; }
            else if (res3 == 1) { fake_idx = 4; fake_type = -1; }
            else { fake_idx = 0; fake_type = 1; }
        }
        else {
            // 假币b(1)重
            fake_idx = 1; fake_type = 1;
        }
    }
    else {
        // abc < def → 对称处理
        int second_left[] = { 0,3,4 }, second_right[] = { 1,6,7 };
        int res2 = balance(second_left, 3, second_right, 3);
        if (res2 == 0) {
            int c_left[] = { 2 }, c_right[] = { 0 };
            int res3 = balance(c_left, 1, c_right, 1);
            if (res3 == -1) { fake_idx = 2; fake_type = -1; }
            else { fake_idx = 5; fake_type = 1; }
        }
        else if (res2 == -1) {
            int d_left[] = { 3 }, d_right[] = { 4 };
            int res3 = balance(d_left, 1, d_right, 1);
            if (res3 == 1) { fake_idx = 3; fake_type = 1; }
            else if (res3 == -1) { fake_idx = 4; fake_type = 1; }
            else { fake_idx = 0; fake_type = -1; }
        }
        else {
            fake_idx = 1; fake_type = -1;
        }
    }

    printf("假币是: %c，状态: %s\n", names[fake_idx], fake_type == 1 ? "较重" : "较轻");
}

int main() {
    // 测试用例1：d是轻假
    memset(coins, 0, sizeof(coins));
    coins[3] = -1;
    printf("测试用例1：d是轻假 → ");
    find_counterfeit();

    // 测试用例2：c是重假
    memset(coins, 0, sizeof(coins));
    coins[2] = 1;
    printf("测试用例2：c是重假 → ");
    find_counterfeit();

    // 测试用例3：h是轻假
    memset(coins, 0, sizeof(coins));
    coins[7] = -1;
    printf("测试用例3：h是轻假 → ");
    find_counterfeit();

    return 0;
}