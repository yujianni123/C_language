#define _CRT_SECURE_NO_WARNINGS 1


//问题描述：假设银行有K个挞口提供服务，窗口前设一条黄线，所有顾客按到达时间在黄线后排成一条长龙。
//当有窗口空闲时，下一位顾客即去该窗口处理事务。当有多个窗口可选择时，假设顾客总是选择编号最小的窗口。
//
//有些银行会给VIP客户以各种优惠服务，例如专门开辟VIP窗口。为了最大限度地利用资源，VIP窗口的服务机制定义为：
//当队列中没有VIP客户时，该挞口为普通顾客服务；当该窗口空闲并且队列中有VIP客户在等待时，排在最前面的VIP客户享受该窗口的服务。
//同时，当轮到某VIP客户出列时，若VIP窗口非空，该客户可以选择空闲的普通窗口；否则一定选择VIP窗口。
//
//本题要求输出前来等待服务的N位顾客的平均等待时间、最长等待时间、最后完成时间，并且统计每个窗口服务了多少名顾客。
//
//输入要求：输入第1行给出正整数N（≤1000），为顾客总人数；随后N行，每行给出一位顾客的到达时间T、事务处理时间P和是否VIP的标志（1是VIP，0则不是），
//并且假设输入数据已经按到达时间先后排好了顺序；最后一行给出正整数K（≤10）—— 为开设的营业窗口数，以及VIP挞口的编号（从0到K−1）。
//这里假设每位顾客事务被处理的最长时间为60分钟。
//
//输出要求：在第一行中输出平均等待时间（输出到小数点后1位）、最长等待时间、最后完成时间，之间用1个空格分隔，行末不能有多余空格。
//在第二行中按编号递增顺序输出每个窗口服务了多少名顾客，数字之间用1个空格分隔，行末不能有多余余空格。
//输入样例：
//10
//0 20 0
//0 20 0
//1 68 1
//1 12 1
//2 15 0
//2 10 0
//3 15 1
//10 12 1
//30 15 0
//62 5 1
//3 1
//输出样例：
//15.1 35 67
//4 5 1


#include <stdio.h>
#include <stdlib.h>

#define MAX_CUSTOMERS 1000
#define MAX_WINDOWS 10

typedef struct {
    int arriveTime;
    int serviceTime;
    int isVIP;
    int startTime;
    int endTime;
    int waitTime;
} Customer;

Customer customers[MAX_CUSTOMERS];
int customerCount = 0;
int windowCount = 0;
int vipWindowIndex = -1;

int windows[MAX_WINDOWS] = { 0 }; // 记录每个窗口的结束时间
int windowsServed[MAX_WINDOWS] = { 0 }; // 记录每个窗口服务的客户数量

// 查找下一个可用窗口
int findNextAvailableWindow(int isVIP) {
    if (isVIP && windows[vipWindowIndex] == 0) {
        return vipWindowIndex;
    }
    int minIndex = -1;
    int minTime = 24 * 60; // 一天的最大分钟数
    for (int i = 0; i < windowCount; i++) {
        if (windows[i] <= minTime) {
            minTime = windows[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void processCustomers() {
    int currentTime = 0;
    int customerIndex = 0;
    int totalWaitTime = 0;
    int maxWaitTime = 0;
    int lastEndTime = 0;

    while (customerIndex < customerCount || currentTime < customers[customerCount - 1].arriveTime + 60) {
        // 处理到达的客户
        while (customerIndex < customerCount && customers[customerIndex].arriveTime <= currentTime) {
            Customer c = customers[customerIndex++];
            int windowIndex = findNextAvailableWindow(c.isVIP);
            if (windowIndex != -1) {
                c.startTime = windows[windowIndex]; // 使用窗口的当前时间作为开始时间
                c.endTime = c.startTime + c.serviceTime;
                c.waitTime = c.startTime - c.arriveTime;
                totalWaitTime += c.waitTime;
                if (c.waitTime > maxWaitTime) {
                    maxWaitTime = c.waitTime;
                }
                lastEndTime = c.endTime;
                windows[windowIndex] = c.endTime; // 更新窗口的结束时间
                windowsServed[windowIndex]++;
            }
        }

        // 更新当前时间
        int minTime = 24 * 60;
        for (int i = 0; i < windowCount; i++) {
            if (windows[i] != 0 && windows[i] < minTime) {
                minTime = windows[i];
            }
        }
        currentTime = (minTime > currentTime) ? minTime : currentTime + 1; // 更新为最早空闲窗口的时间或当前时间加1
    }

    double averageWaitTime = (double)totalWaitTime / customerCount;

    printf("%.1f %d %d\n", averageWaitTime, maxWaitTime, lastEndTime);
    for (int i = 0; i < windowCount; i++) {
        printf("%d ", windowsServed[i]);
    }
    printf("\n");
}

int main() {
    int N, K;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &customers[i].arriveTime, &customers[i].serviceTime, &customers[i].isVIP);
        customers[i].waitTime = 0;
        customerCount++;
    }
    scanf("%d %d", &K, &vipWindowIndex);
    windowCount = K;

    processCustomers();

    return 0;
}