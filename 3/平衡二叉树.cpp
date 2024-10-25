/*
平衡二叉树
1.左右子树的高度的绝对值差不超过1
2.最小失衡子树：距离插入节点最近的失衡节点
3.  RR:插入位置是失衡节点右子树的右子树
	1.中值法，中值作为失衡子树的根

	LL:插入位置是失衡节点左子树的左子树
	1.中值法，中值作为失衡子树的根


	LR:插入位置是失衡节点左子树的右子树
	1.在插入节点的右子树插入一个空节点，转换成LRR，
	2.对RR进行转化，将LRR转化成（删除空节点）LL
	3.采用LL的方法进行解决

	RL:插入位置是失衡节点右子树的左子树
	1.在插入节点的左子树插入一个空节点，转换成RLL，
	2.对LL进行转化，将RLL转化成（删除空节点）RR
	3.采用RR的方法进行解决





*/