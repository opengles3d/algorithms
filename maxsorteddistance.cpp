#include <iostream>
#include <vector>

struct Bucket {
     int min;
     bool minset;
     int max;
     bool maxset;
 };

int getMaxSortedDistance(const std::vector<int>& array){
    //1.得到数列的最大值和最小值
    int max = array[0];
    int min = array[0];
    for(int i = 1; i < array.size(); i++){
        if(array[i] > max){
            max = array[i];
        }
        if(array[i] < min){
            min = array[i];
        }
     }
     int d = max - min;
     if(d == 0){
         return 0;
     }

     //2.初始化桶
     int bucketNum = array.size();
     std::vector<Bucket> buckets(bucketNum);
     //3.遍历原始数组，确定每个桶的最大最小值
     for(int i = 0; i < array.size(); i++){
         //确定数组元素所归属的桶下标
         int index = ((array[i] - min)  * (bucketNum - 1) / d);
         if(buckets[index].minset == false) {
             buckets[index].minset = true;
             buckets[index].min = array[i];
         }else if(buckets[index].min > array[i]){
             buckets[index].min = array[i];
         }

         if(buckets[index].maxset == false){
             buckets[index].maxset = true;
             buckets[index].max = array[i];
         }else if(buckets[index].max<array[i]){
             buckets[index].max = array[i];
         }
     }

     //4.遍历桶，找到最大差值
     int leftMax = buckets[0].max;
     int maxDistance = 0;
     for(int i = 1; i < buckets.size(); i++){
         if(!buckets[i].minset){
             continue;
         }
         if(buckets[i].min - leftMax > maxDistance){
             maxDistance = buckets[i].min - leftMax;
         }
         leftMax = buckets[i].max;
     }

     return maxDistance;
 }



int main(int argc, char* argv[]) {
     std::vector<int> array{100, 6, 3, 4, 5, 18, 9};
     std::cout << "Max sorted distance is : " << getMaxSortedDistance(array);
     return 0;
 }