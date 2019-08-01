# RedBlackTree
一行一注释 详细讲解红黑树插入与删除操作 并且附带可视化打印操作
              深入浅出RBT
一：前言
作为数据结构学习中的一个高级数据结构，红黑树以其高效的查找、插入 、删除操作在树这个结构中绝对是有一席之地的，但是又由于其复杂的情况讨论，令不少人望而
却步，在网上有不少的关于红黑树分析的文章，可能是表达不当，其文章的质量层次不齐，本来红黑树的考虑情况就比较多，不同的人的操作方法还不同，使得很多想学红
黑树的同学看得更加晕头转向，而事实上红黑树并没有我们看到的那么难，觉得难是在于树平衡操作的基础没打好，而不在与红黑树本身难到没办法学，鉴于此网上文章质
量良莠不齐，便写下了这篇文章，有不足之处还望指正
二：红黑树基本性质与红黑性质的维护方法
红黑树基本性质：
1.	每个结点要么是红色，要么是黑色
2.	树的根必须是黑色的
3.	如果一个结点是红色的，那么它的子结点必须是黑色的
4.	从任意一个结点到任意一个终端结点（nullptr）的每一条路径都必须包含相同数目的黑色结点
维护红黑性质的方法
1.	左旋转  2.右旋转  3.单旋转  4.双旋转（之字型）
左旋转 右旋转 不详讲解
单旋转
对三个结点的中间结点进行左右旋转
双旋转（之字形）
对三个结点的后两个和前两分别进行一次单旋
这四种是方法是有区别的，比如前两个方法是对与两个结点而言的，后面的两个是对三个结点而言的，上述图片来源于网络，具体的详细操作不想赘述，本文还是想具体简
述红黑树的中的难点操作插入与删除

插入
根据红黑树的性质我们知道如果插入一个红色结点是不会破坏红黑树的性质，但是如果要插入一个红色结点就必须要插入结点的父亲结点为黑色，否则会出现两个连续的红
色结点，，那要是其父亲结点为红色该怎么办呢？其实也很简单，那就是旋转，在这里我们先假设如果插入结点的父亲结点的兄弟结点是黑色的（如果有的话），这时就有
两种情况（没有算对称情况），分别用单旋转（并将其祖父结点变成红色）和双旋转（并将其本身变成黑色，祖父结点变成红色），可以轻松解决，但是如果其兄弟结点是
红色的呢？其实方法也很简单，那就是当一个结点的左右儿子结点都为红色的时候进行一次颜色翻转，将其本身变成红色，儿子变成黑色，这样当然是不会破坏红黑树的性
质的，但是新的问题又来了，如果这样颜色翻转后，上一层又出现了两个连续的红色结点该怎么办？答案是，继续向上旋转、翻转递推，但是如果这样，那就必须要用一个
栈去储存路径，这样相当的麻烦，而我们的解决方法是自定向下进行插入，具体的方法还是不变，因为是自顶向下插入，插入结点的父亲结点的兄弟结点就不可能是红色的
了，这样无形中也简化了操作

删除
红黑树最大的难点就在其删除操作上了，这也是网上大多数文章没表达清楚的主要的地方了，很多文章中的删除操作分了很多种情况，让读者难以理解，而在这里我想向大
家介绍一种最简单的删除方法，在讲解之前我要附带说一个东西，方便后面的删除，那是nullNode结点和header假根，其实这两个东西在插入操作中也很用到，很简单的
两个东西可以为我们的操作带来极大的方便，我们定义空结点为nullNode，而空树为以header为根的一棵树，其一个儿子是nullNode,另一个儿子为nullNode（Root
真根），这样其时我们就不用考虑不存在父亲的结点情况了，好现在进入我们的删除操作讲解，删除操作分两步进行，第一步查找待删除的结点，找到这个结点后我们看这
个结点的儿子数，1.如果没有儿子那待删除就是该结点，2.如果有一个儿子，由于红黑树的性质，只有一个儿子的结点必定是叶子结点的父亲，那就把该删除结点的值与
其儿子的值交换（颜色不交换），这转化为了情况1，此时待删除是其儿子结点，如果有两个儿子，那么将待删除结点的值变成其右子树的的最小结点的值，此时待删除结点
就在其右子树的中删除其最小结点，最终我们可以把这些情况都归结为删除红黑树的叶子结点，然后第二步，就是删除结点，分为两大部分，第一部分：不需要调整红黑树，
如果最后的实际删除结点的颜色为红色，就可以直接删除，因为删除该结点不会破坏红黑树的性质，第二部分：需要调整红黑树，这一部分中我们考虑若何想办法让实际删
除的结点变成红色，，同样是自顶向下，同样是由于自顶向下查找，可以保证在每一步开始时其父亲结点必然是红色，其当前结点和其兄弟结点的颜色必然是黑色的，每一
步结束时当前的结点必然是红色的，方法如下：
一：我们先将其树根变成红色，然后观察其儿子的颜色情况，如果其儿子都是黑色那就进行第二步，如果其中有红色就进行四步
二：.观察当前结点的儿子结点是否有红色结点，如果没有进行第三步，如果有进行四步
三：1.如果当前结点的兄弟结点的儿子都是黑色的，那么就将其父亲结点变成黑色，当前结点及其兄弟结点变成红色，2.如果当前结点的兄弟结点的儿子中有红色的，那
么根据父亲结点，兄弟结点，兄弟结点的儿子的排列顺序进行单旋转（并将其兄弟结点和当前结点颜色变成红色，兄弟结点的红色儿子和其父亲变成黑色），双旋转（之字
形）
（并将其父亲的结点变成黑色，当前结点变成红色）
四：先直接进行下一步，如果当前结点正好落在其红色结点上，那就不需要调整，直接下一步，否则根据当前结点和其儿子的排列顺序进行左右旋转（并将当前结点的颜色
和其红色儿子的颜色对换）
五：重复上述操作直到当前结点时实际的删除结点，将其删除，并将根恢复为黑色，即可


至此红黑树的插入与删除全部讲解完成，看完后其实都会发现看似很难的红黑树实际分析的时候也不是很难了，最后这篇文章中讲述的红黑树代码在GitHub上，代码注释
得非常清楚，插入与删除操作几乎每一行的有注释，还附带了可视化打印操作
链接：https://github.com/yfismine/RedBlackTree
