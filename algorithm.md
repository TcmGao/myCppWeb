### 背包问题
0. 什么是背包问题，背包问题的描述是，一件物品有重量和价值，而一个背包有最大容量，求如何才能使得价值最大。
也就是说，背包问题实质是我们的某些东西有两个变量，我们需要在使得某一个变量的和不超过固定值时，计算另一个变量和的最大值。
背包问题是典型的二维动态规划，偷窃房屋时，只需要想着当前房屋偷与不偷分别能达到的最大价值。而当遇到背包时，还需要考虑另一个变量的限制，也就是容量。如果偷房屋有所偷房屋个数限制，那么就变成了背包问题。

1. 01背包，有N件物品和容量为V的背包，每件物品价值为Wi，体积为Ci，求最大价值，每种物品只有一件。
  * 01背包是最典型的背包，dp思路为:
    ```
    dp[i][v]表示前i件物品放入容量为v的背包的最大价值
    dp[i][v] = max(dp[i-1][v], dp[i-1][v-Ci] + Wi)，也就是第i件物品选择放与不放时得到的最大价值。
    显然，此时需要两层遍历，一层遍历物品，另外一层就是遍历背包容量。
    for (int i = 1; i <= N; ++i) {
      for (int v = 1; v <= V; ++v) {
        dp[i][v] = max(dp[i-1][v], dp[i-1][v-C[i]] + W[i]);
      }
    }
    ```
  * 两层遍历，那我们就从二维数组的角度去想，这里假设dp[i-1][v-C[i]]==dp[i-1][v-1]，即V[i]==1。能不能优化空间复杂度？
    |  (i-1, v-1)      |  (i-1, v)     |
    |------------------|---------------|
    |   **(i, v-1)**   |   **(i, v)**  |

    很明显，当前行依赖上一行，所以我们完全可以用两个一维数组滚动解决问题。
    由于只依赖上一行，所以可以再减少一个数组，只用一个数组。
    我们总想着计算出(i,v)的数据后，就覆盖(i-1,v)。
    但是每一行都是从前往后计算的，所以会有问题，因为(i,v)依赖(i-1,v-1)，而我们在计算(i,v-1)后就覆盖了(i-1,v-1)。
    而(**i,v**)的计算是不依赖(**i,v-1**)的，所以我们完全可以对**每一行倒序计算**。这样就不存在问题了，变成以下这样
    ```
    for (int i = 1; i <= N; ++i) {
      for (int v = V; v >= 1; --v) {
        dp[v] = max(dp[v], dp[v-C[i]] + W[i]);
      }
    }
    ```
    **至此，01背包得到最优时空复杂度的解法**。
  * **关于初始化问题**：查看初始状态是否合法，对于01背包来说，一件物品也不装是合法的，所以dp[i][0]和dp[0][v]都是0。而对于某些背包而言，要求装满背包，那么dp[i][0]是合法的，但是dp[0][v]显然不合法，dp[i][v]在没有计算时，显然是不合法的初始化为负无穷

2. 完全背包：完全背包在01背包上升级，每种物品的件数是无限的。
  * 此时问题变得复杂，因为dp[i,v]只能表示第i种物品，那么我们就需要遍历判断第i种物品的件数
    ```
    dp[i][v] = max(dp[i-1][v-kCi] + kWi),其中，0 <= kCi <= v
    ```
  * 此时转为01背包，复杂度明显上升了，那么是否可以想其他方法。现在还是假设C[i]==1，那么实际上没有必要计算第i件物品取0...v件。
    * dp[i][v] 依赖dp[i-1][v]，即第i种物品不取。
    * dp[i][v] 实际上只需要再依赖dp[i][v-1]，前i种物品放入v-1的背包可以获得的最大值，然后再加入一个物品就可以组成(i,v)。为什么可以，仔细来看表格的转换。
    
      | (i-1,v-4) | (i-1,v-3) | (i-1,v-2)  | (i-1,v-1)  | (i-1,v) |
      |-----------|-----------|------------|------------|---------|
      |**(i,v-4)**|**(i,v-3)**|**(i,v-2)** |**(i,v-1)** |**(i,v)**|
    * (i,v) = max{(i-1,v), (i-1,v-1) + 1, (i-1,v-2) + 2, (i-3, v-3) + 3}
    * (i,v-1) = max{(i-1,v-1),(i-1,v-2) + 1, (i-3, v-3) + 2}
    * 显然，从数学上看也是成立的。
    * **那么问题来了，为什么01背包不能用这个子问题呢？**
    * **因为01背包不能重复取，当我们决定取i时，(i,v-Ci)是一定不能作为子问题的**
    * **而完全背包是我们恰好需要这个子问题**