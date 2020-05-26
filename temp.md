```c++
// 辅助函数，在当前结点上找到第一个大于等于目标关键字k的索引位置
int BTreeNode::findKey(int k) {
    int idx = 0;
    while(idx<n && keys[idx] < k) {
        ++idx; // 如果目标k还是太大，则继续向后找
    }
    return idx;
}
// 从当前结点（叶子结点）上移除第idx位的关键字(k),(1)
void BTreeNode::removeFromLeaf(int idx) {
    // 直接将目标关键字移除（后面的关键字都往前移
    for (int i = idx+1; i < n; i++) {
        keys[i-1] = keys[i];
    }
    // 度数也减去1
    --n;
    return;
}
// 在当前结点上，获得第idx位关键字的前驱关键字(k'),(2.a)
int BTreeNode::getPred(int idx) {
    // 找到左子树上的最大key
    BTreeNode *cur=children[idx]; // children[idx]就是第idx位关键字的前驱
    // 因为B-Tree是平衡树，所以，如果当前结点不是叶子结点，则他必有最右子结点第n位
    while(!cur->leaf) {
        cur = cur->children[cur->n]; // 度是n，子结点数量是n+1
    }
    // 最后叶子结点的最右边的key，则为最大前驱
    return cur->keys[cur->n-1];
}
// 在当前结点上，获取第idx位关键爱你字的后继关键字(k'),(2.b)
int BTreeNode::getSucc(int idx) {
    // 找到右子树的最小key
    BTreeNode *cur=children[idx+1]; // children[idx+1]就是第idx位关键字的后继结点
    // 平衡树，不是也子结点，就必须有左子结点
    while(!cur->leaf) {
        cur = cur->children[0];
    }
    // 最左边的key，则为最小后继
    return cur->keys[0];
}
// 把第idx个子结点和第idx+1个子结点，以及第idx个关键字合并
// 这个合并的前提应该是第idx个关键字k的左右两个子结点都只包含t-1的度(2.c/3.b)
// 合并后的新结点在第idx位
void BTreeNode::merge(int idx) {
    /*
    //              [idx]
    //             /     \
    //        (idx)     (idx+1)
    */
    BTreeNode *child = children[idx];
    BTreeNode *sibling = children[idx+1];
    // child有t-1个key, sibling也有t-1个key
    // 目的是将sibling和目标关键字(keys[idx])合到child
    // [child.keys]-[keys[idx]]-[sibling.keys]
    // 目标关键字，在child上应该是在第t-1位
    child->keys[t-1] = keys[idx];
    // 接着把sibling的keys也copy过来
    for (int i = 0; i <sibling->n; ++i) {
        child->keys[t+i] = sibling->keys[i];
    }
    // copy完keys，还要copy子树部分
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i) {
            child->children[t+i] = sibling->children[i];
        }
    }
    // 合并后的左子树，度数变为2t-1
    child->n += sibling->n + 1;
    // 现在已经把左子树，目标关键字，右子树合成了一个新的结点（左子树）
    // 接着需要将目标关键字在当前结点上移除
    // 首先移动keys部分
    for (int i = idx+1; i < n; ++i) {
        keys[i-1] = keys[i];
    }
    // 接着把子树也向左移动一格
    // idx位置的左子树不变，idx+1位置的右子树已经被合并调了
    // 移动是从idx+2移到idx+1开始
    for (int i = idx + 2; i <= n; ++i) {
        children[i-1] = children[i];
    }
    // 当前结点，由于去掉了一个目标结点，合并了两个子树到一个子树
    // 度数需要-1
    n--;
    // 合并完之后,右子树被释放
    delete(sibling);
    return;
}
// 从当前结点（非叶子结点）上移除第idx位的关键字(k), (2)
void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx]; // 暂存目标关键字
    // 判断左子树是否满足>=t的度数条件
    if (children[idx]->n >= t) {
        // 从左子树找最大前驱
        int pred = getPred(idx);
        // 在左子树上，将pred(k')删除
        children[idx]->remove(pred);
        // 再将k替换为k'
        keys[idx] = pred;
    } else if (children[idx+1]->n >= t) {
        // 判断有子树是否满足>=t的度数条件
        // 从右子树找最小后继
        int succ = getSucc(idx);
        // 在右子树上，将succ(k')删除
        children[idx+1]->remove(succ);
        // 再将k替换为k'
        keys[idx] = succ;
    } else {
        // 如果左子树和右子树的度数都仅位t-1，则需要将左子树和右子树以及目标关键字左合并
        merge(idx);
        // 继而在合并的结点上进行第归删除
        children[idx]->remove(k);
    }
}
// 关键字在第idx个子结点上，且该子结点只有t-1的度
// 但是该子结点的左兄弟有至少t的度，则从他的左兄弟(prev)
// 借一个关键字（左兄弟上的最大关键字）提升到当前结点
// 把当前结点上介于左兄弟和目标子结点之间的关键字下降到目标子结点(3.a)
void BTreeNode::borrowFromPrev(int idx) {
    // 目标子树是第idx位，因此要从当前结点移到目标结点的关键字是第idx-1位的关键字
    /*
    //              [idx-1][idx]
    //             /      |      \
    //      (idx-1)      (idx)     (idx+1)
    */
    BTreeNode *child = children[idx];
    BTreeNode *prev = children[idx-1];
    // 首先是把child子树上的关键字，全部往后面挪一位，让出空间给准备从当前结点第idx-1位下降下来的关键字
    for (int i = child->n-1; i >= 0; --i) {
        child->keys[i+1] = child->keys[i];
    }
    // 如果是child不是叶子结点，则child的子树，也得往后挪一位
    if (!child->leaf) {
        for (int i = child->n; i >=0; --i){
            child->children[i+1] = child->children[i];
        }
    }
    // 挪好之后，把目标关键字移下来
    child->keys[0] = keys[idx-1];
    // 别忘了，这个时候，child的第0为的子树被往后移了一格，已经空了
    // 我们需要将prev的最后一个子树挂过来
    if (!child->leaf) {
        child->children[0] = prev->children[prev->n];
    }
    // 显然挂完之后，child的度多1
    child->n += 1;
    // 接着，prev的最后一个key(第n-1位)要上移到当前结点的idx-1的位置
    keys[idx-1] = prev->keys[prev->n-1];
    // prev子结点由于上移了一个关键字，度数减1
    // 度数减一之后，原来最左边的那个子树，就相当于抹掉了
    prev->n -= 1;
    return;
}
// 关键字在第idx个子结点上，且该子结点只有t-1的度
// 但是该子结点的右兄弟有至少t的度，则从他的右兄弟(next)
// 借一个关键字（右兄弟上的最小关键字）提升到当前结点
// 把当前结点上介于目标子结点和右兄弟之间的关键字下降到目标子结点(3.a)
void BTreeNode::borrowFromNext(int idx) {
    // 和borrowFromPrev的旋转方向正好相反
    // 目标子树是第idx位，因此要从当前结点移到目标结点的关键字是第idx位的关键字
    /*
    //              [idx-1][idx]
    //             /      |      \
    //     (idx-1)      (idx)     (idx+1)
    */
    BTreeNode *child = children[idx];
    BTreeNode *next = children[idx+1];
    // 把当前结点的第idx位的key移到目标子树child的keys中，放在最右侧
    child->keys[child->n] = keys[idx];
    // 同时，next的最左子树需要挂到child的最右侧
    if (!child->leaf) {
        child->children[(child->n)+1] = next->children[0];
    }
    // child子树的挪东已经完成，由于多增加了一个从当前结点落下来的key
    // 度数将增加1
    child->n += 1;
    // 接着，当前结点的keys部分,第idx位的key需要被右子树next的第一个key替换
    keys[idx] = next->keys[0];
    // 最后需要对右子树next进行调整
    // keys部分往左移一格
    for (int i = 1; i < next->n; ++i) {
        next->keys[i-1] = next->keys[i];
    }
    // 子树部分也往左移动一个
    if (!next->leaf) {
        for (int i = 1; i <= next->n; ++i) {
            next->children[i-1] = next->children[i-1];
        }
    }
    // 由于next最左边的关键字和子树被提走了，度数相应的减一
    next->n -= 1;
    return;
}
// 目标关键字不在当前结点上，idx是我们需要进一步第归的目标关键字
// 可能在的第idx个子结点，通过fill保证children[idx]的度不低于t
// 其处理了两中场景：3.a和3.b
// 3.a: 虽然children[idx]只有t-1的度，但是他有兄弟是t及以上的
//      通过旋转，完成子结点的度提升
// 3.b: children和他兄弟都只有t-1的度，就通过merge来完成子结点度的提升
// 返回fill之后的目标分支
int BTreeNode::fill(int idx) {
    int targetIdx = idx; // 默认在fill之后，目标分支还是idx
    // 如果左子树度数有多，则从左子树借
    if (idx != 0 && children[idx-1]->n >= t) {
        borrowFromPrev(idx);
    } else if (idx != n && children[idx+1]->n >= t) {
        // 如果右子树度数有多，则从右子树借
        borrowFromNext(idx);
    } else {
        // 如果左右子树都只有t-1，没有多于的
        // 如果不是最右的子树，则将目标子树和右边的子树合并
        // 合并后，还是挂在idx位
        if (idx != n)
            merge(idx);
        else {
            merge(idx-1);  // 注意，如果是在idx-1上进行的merge，则目标分支由原来的idx，变为idx-1!
            targetIdx = idx-1;
        }
    }
    return targetIdx;
}
// 基于当前结点删除关键字k
bool BTreeNode::remove(int k) {
    // 首先在当前结点上找到大于等于目标k的索引位置
    int idx = findKey(k);
    if (idx < n && keys[idx] == k) {
        // 如果正好找到了，则进一步判断当前结点是否位叶子结点
        if (leaf) {
            removeFromLeaf(idx);
        } else {
            removeFromNonLeaf(idx);
        }
        return true;// 总归是找到了，就返回true
    } else {
        // 如果没找到，那idx就是目标分支
        if (leaf) {
            // 如果已经到叶子结点了，都没找到，则找不到该key了
            return false;
        }
        // 接着判断，是否需要执行场景3的补足操作
        if (children[idx]->n < t) {
            idx = fill(idx);
        }
        // 补足之后，继续第归，在目标子树上进行移除
        return children[idx]->remove(k);
    }
}
bool BTree::remove(int k) {
    if (root == nullptr) {
        return false;
    }
    bool res = true;
    res = root->remove(k);
    // 如果remove完之后，度数已经降到0，则有两种情况
    // 要么已经没有数据了， 要么还有一个子结点，得降高度
    if (root->n == 0) {
        BTreeNode *tmp = root;
        if (root->leaf) {
            root = nullptr;
            // 什么时候root->leaf会变成true？
            // 只有在最后，先进入下面的else分支时，这个时候，root已经变成了root->children[0]
            // 而root->children[0]的leaf就是true，也就是新的root->leaf为true.
        } else {
            root = root->children[0];
        }
        // 释放老root
        delete tmp;
    }
    return res;
}
```
