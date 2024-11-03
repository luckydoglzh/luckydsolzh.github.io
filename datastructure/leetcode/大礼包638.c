// 在 LeetCode 商店中， 有 n 件在售的物品。每件物品都有对应的价格。然而，也有一些大礼包，每个大礼包以优惠的价格捆绑销售一组物品。

// 给你一个整数数组 price 表示物品价格，其中 price[i] 是第 i 件物品的价格。另有一个整数数组 needs 表示购物清单，其中 needs[i] 是需要购买第 i 件物品的数量。

// 还有一个数组 special 表示大礼包，special[i] 的长度为 n + 1 ，其中 special[i][j] 表示第 i 个大礼包中内含第 j 件物品的数量，且 special[i][n] （也就是数组中的最后一个整数）为第 i 个大礼包的价格。

// 返回 确切 满足购物清单所需花费的最低价格，你可以充分利用大礼包的优惠活动。你不能购买超出购物清单指定数量的物品，即使那样会降低整体价格。任意大礼包可无限次购买。

// 思路：
// 该问题一般用回溯法解决
int minmoney(int* price, int priceSize, int** special, int specialSize, int* specialColSize, int* needs, int needsSize, int money, bool *buy) {
    int i;
    int min=1000;
    for(i=0;i<needsSize;i++) {         
        if(needs[i]!=0) {
            break;
        }
    }
    if(i==needsSize) {                          //递归结束条件
        return money;
    }
    int *needs1=malloc(sizeof(int)*needsSize); //由于每次传递的needs有变化，所以需创造一个新的needs
    for(i=0;i<needsSize;i++) {
        needs1[i]=needs[i];
    }
    int isok=0;                               //如果所有大礼包都用不了了，就直接计算总价并返回
    int temp;                                 //判断礼包能否使用
    for(i=0;i<specialSize;i++) {
        if(buy[i]==false) {                   //判断礼包是否真的优惠
            continue;
        }
        temp=0;
        for(int j=0;j<needsSize;j++) {
            if(needs1[j]-special[i][j]<0) {
                temp=1;
                break;
            }
        }
        if(temp==0){                         //礼包优惠且可用
            for(int j=0;j<needsSize;j++) {   
            needs1[j]-=special[i][j];
            }
            isok=1;                          //由于用了礼包，所以不能直接计算总价
            min=fmin(minmoney(price,priceSize,special,specialSize,specialColSize,needs1,needsSize,money+special[i][priceSize],buy),min);
            for(int j=0;j<needsSize;j++) {
            needs1[j]+=special[i][j];
            }
        }
    }
    if(isok==0) {                          //无礼包可用，直接计算总和并返回
        min=money;
        for(int i=0;i<needsSize;i++) {
            min+=needs1[i]*price[i];
        }
    }
    return min;
}
int shoppingOffers(int* price, int priceSize, int** special, int specialSize, int* specialColSize, int* needs, int needsSize){
    bool *buy=malloc(sizeof(bool)*specialSize);                //判断每个大礼包是否真的优惠
    int num;
    for(int i=0;i<specialSize;i++) {0
        num=0;
        for(int j=0;j<priceSize;j++) {
            num+=special[i][j]*price[j];
        }
        if(num>special[i][priceSize]) {
            buy[i]=true;
        }
        else {
            buy[i]=false;
        }
    }
    return minmoney(price,priceSize,special,specialSize,specialColSize,needs,needsSize,0,buy);
}
