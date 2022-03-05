#include "graph.h"
#if _MSC_VER >=1600
#pragma execution_character_set("utf-8")
#endif
Graph::Graph()
{

}
Graph::~Graph()
{

}
string Graph::Inquire_SpotInfo1(int x)
{
	return G.S[x - 1].introduction;
}
string Graph::ShortestPathTwo(int start, int end)
{
	int Di[40][40];
	for (int i = 0; i < G.n; i++)
		for (int j = 0; j < G.n; j++)
			Di[i][j] = G.P[i][j].dis;
	return Floydd(Di, start, end);
}
string Graph::BestPersonWay(int start, int end)
{
	int Di[40][40];
	for (int i = 0; i < G.n; i++)
		for (int j = 0; j < G.n; j++) {
			if (G.P[i][j].pathtype == 1) {
				Di[i][j] = MAX;
			}
			else {
				Di[i][j] = G.P[i][j].dis;
			}
		}
	return Floydd(Di, start, end);
}
string Graph::BestCarWay(int start, int end)
{
	int Di[40][40];
	for (int i = 0; i < G.n; i++)
		for (int j = 0; j < G.n; j++) {
			if (G.P[i][j].pathtype == 0) {
				Di[i][j] = MAX;
			}
			else {
				Di[i][j] = G.P[i][j].dis;
			}
		}
	return Floydd(Di, start, end);
}
string Graph::Cheapest(int start, int end)
{
	int Di[40][40];
	for (int i = 0; i < G.n; i++)
		for (int j = 0; j < G.n; j++) {
			if (G.P[i][j].dis < MAX) {
				Di[i][j] = G.S[j].price;
			}
			else {
				Di[i][j] = MAX;
			}
		}
	return Floydd(Di, start, end);
}
string Graph::BestSpots(int start, int end)
{
	int Di[40][40];
	for (int i = 0; i < G.n; i++)
		for (int j = 0; j < G.n; j++) {
			if (G.P[i][j].dis < MAX) {
				Di[i][j] = 5 - G.S[j].rank;
			}
			else {
				Di[i][j] = MAX;
			}
		}
	return Floydd(Di, start, end);
}
string Graph::ShortestTimePath(int begin, int end)
{
	result1 = "";
	double subdis, busdis, bikedis, taxidis, walkdis, mindis;
	Floyd(G);
	walkdis = dis[begin - 1][end - 1];
	mindis = walkdis;
	Floyd(SubG);
	subdis = dis[begin - 1][end - 1];
	mindis = (mindis < subdis) ? mindis : subdis;
	Floyd(BusG);
	busdis = dis[begin - 1][end - 1];
	mindis = (mindis < busdis) ? mindis : busdis;
	Floyd(BikeG);
	bikedis = dis[begin - 1][end - 1];
	mindis = (mindis < bikedis) ? mindis : bikedis;
	Floyd(TaxiG);
	taxidis = dis[begin - 1][end - 1];
	mindis = (mindis < taxidis) ? mindis : taxidis;
	if (mindis == walkdis)
	{
		Floyd(G);
		result1.append("步行用时最短，路径如下：");
		result1.append(G.S[begin - 1].name);
		result1.append("->");
		FloydPath(G, begin - 1, end - 1);
		result1.append(G.S[end - 1].name);
		return result1;
	}
	else if (mindis == subdis)
	{
		Floyd(SubG);
		result1.append("乘坐地铁用时最短，路径如下：");
		result1.append(SubG.S[begin - 1].name);
		result1.append("->");
		FloydPath(SubG, begin - 1, end - 1);
		result1.append(SubG.S[end - 1].name);
		return result1;
	}
	else if (mindis == busdis)
	{
		Floyd(BusG);
		result1.append("乘坐公交车用时最短，路径如下：");
		result1.append(BusG.S[begin - 1].name);
		result1.append("->");
		FloydPath(BusG, begin - 1, end - 1);
		result1.append(BusG.S[end - 1].name);
		return result1;
	}
	else if (mindis == bikedis)
	{
		Floyd(BikeG);
		result1.append("骑自行车用时最短，路径如下：");
		result1.append(BikeG.S[begin - 1].name);
		result1.append("->");
		FloydPath(BikeG, begin - 1, end - 1);
		result1.append(BikeG.S[end - 1].name);
		return result1;
	}
	else
	{
		Floyd(TaxiG);
		result1.append("乘坐出租车用时最短，路径如下：");
		result1.append(TaxiG.S[begin - 1].name);
		result1.append("->");
		FloydPath(TaxiG, begin - 1, end - 1);
		result1.append(TaxiG.S[end - 1].name);
		return result1;
	}
}
string Graph::BestPath(int num, int visit[40])
{
	result1 = "";
	dist = MAX;
	dist1 = 0;
	Floyd(G);
	//回溯法求出所有路径组合并将最短路径存在result中
	pathindex = 0;
	BackTracking(visit, num, 0);
	//输出最短路径
	result1.append("最佳路径为：");
	for (int i = 0; i < num - 1; i++)
	{
		result1.append(G.S[result[i] - 1].name);
		result1.append("->");
		FloydPath(G, result[i] - 1, result[i + 1] - 1);
	}
	result1.append(G.S[result[num - 1] - 1].name);
	return result1;
}
void Graph::FloydSpath(int Spath[40][40], int begin, int end)
{
	if (Spath[begin][end] == -1 || Spath[begin][end] == end || Spath[begin][end] == begin)
	{
		return;
	}
	else
	{
		FloydSpath(Spath, begin, Spath[begin][end]);
		result1.append(G.S[Spath[begin][end]].name);
		result1.append("->");
		FloydSpath(Spath, Spath[begin][end], end);
	}
}
string Graph::Floydd(int Matrix[40][40], int begin, int end)
{
	int i, j, k;
	int dist[40][40];
	int Spath[40][40];
	result1 = "";
	for (i = 0; i < G.n; i++) ///初始化距离与路径矩阵
	{
		for (j = 0; j < G.n; j++)
		{
			dist[i][j] = Matrix[i][j];
			if (i != j && dist[i][j] < MAX)
			{
				Spath[i][j] = i;
			}
			else
			{
				Spath[i][j] = -1;///-1代表不可达
			}
		}
	}
	for (k = 0; k < G.n; k++)
	{
		for (i = 0; i < G.n; i++)
		{
			for (j = 0; j < G.n; j++)
			{
				if (dist[i][j] > (dist[i][k] + dist[k][j]))
				{
					dist[i][j] = dist[i][k] + dist[k][j];///更新
					Spath[i][j] = k;         ///path用于记录最短路径上的结点*/
				}

			}
		}
	}
	result1.append("最佳路线为:");
	result1.append(G.S[begin - 1].name);
	result1.append("->");
	FloydSpath(Spath, begin - 1, end - 1);
	result1.append(G.S[end - 1].name);
	return result1;
}
void Graph::Floyd(Map G)
{
	for (int i = 0; i < G.n; i++)
	{
		for (int j = 0; j < G.n; j++)
		{
			dis[i][j] = G.P[i][j].dis;
			if (i != j && dis[i][j] < MAX)
			{
				middle[i][j] = i;
			}
			else
			{
				middle[i][j] = -1;
			}

		}
	}
	for (int m = 0; m < G.n; m++)
	{
		for (int i = 0; i < G.n; i++)
		{
			for (int j = 0; j < G.n; j++)
			{
				if ((dis[i][m] + dis[m][j]) < dis[i][j])
				{
					dis[i][j] = dis[i][m] + dis[m][j];
					middle[i][j] = m;//m为中间节点，更新在路径中；
				}
			}
		}
	}
}
void Graph::FloydPath(Map G, int start, int end)
{
	if (middle[start][end] == -1 || middle[start][end] == start || middle[start][end] == end)
	{
		return;
	}
	else
	{
		FloydPath(G, start, middle[start][end]);
		result1.append(G.S[middle[start][end]].name);
		result1.append("->");
		FloydPath(G, middle[start][end], end);
	}
}
void Graph::swap(int *a, int index1, int index2)
{
	int temp = a[index1];
	a[index1] = a[index2];
	a[index2] = temp;
}
void Graph::BackTracking(int visitSpot[40], int num, int index)
{
	
	//double dist = MAX;
	//double dist1 = 0;
	if (pathindex == num)
	{
		for (int i = 0; i < num - 1; i++)
		{
			dist1 += dis[path[i]-1][path[i+1]-1];
		}
		if (dist1 < dist)
		{
			for (int j = 0; j < num; j++)
			{
				result[j] = path[j];
			}
			dist = dist1;
			return;
		}
		else
		{
			return;
		}
	}
	for (int i = index; i < num; i++)
	{
		path[pathindex] = visitSpot[i];
		pathindex++;
		swap(visitSpot, index, i);
		BackTracking(visitSpot, num, index + 1);
		swap(visitSpot, index, i);
		pathindex--;
	}
}
void Graph::Creat_Spot()
{
	G.S[0].num = 1;
	G.S[0].name = "大明宫国家遗址公园";
	G.S[0].introduction = "大明宫国家遗址公园是世界文化遗产，全国重点文物保护单位。位于陕西省西安市太华南路，大明宫地处长安城北部的龙首原上，始建于唐太宗贞观八年(634年)，平面略呈梯形。";
	G.S[0].rank = 5;
	G.S[0].price = 0;
	G.S[1].num = 2;
	G.S[1].name = "西安钟鼓楼";
	G.S[1].introduction = "西安钟楼始建于明洪武十七年，原建于今西大街北广济街东侧，明万历十年移于现址。";
	G.S[1].rank = 3;
	G.S[1].price = 0;
	G.S[2].num = 3;
	G.S[2].name = "西安城墙";
	G.S[2].introduction = "西安城墙，是中国现存规模最大、保存最完整的古代城垣，是第一批全国重点文物保护单位、国家AAAAA级旅游景区 。";
	G.S[2].rank = 5;
	G.S[2].price = 50;
	G.S[3].num = 4;
	G.S[3].name = "大唐不夜城";
	G.S[3].introduction = "唐不夜城以盛唐文化为背景，以唐风元素为主线 ，建有大雁塔北广场、玄奘广场、贞观广场、创领新时代广场四大广场。";
	G.S[3].rank = 1;
	G.S[3].price = 0;
	G.S[4].num = 5;
	G.S[4].name = "大雁塔";
	G.S[4].introduction = "大雁塔位于唐长安城晋昌坊（今陕西省西安市南）的大慈恩寺内，又名“慈恩寺塔”。";
	G.S[4].rank = 5;
	G.S[4].price = 50;
	G.S[5].num = 6;
	G.S[5].name = "大唐芙蓉园";
	G.S[5].introduction = "唐芙蓉园位于陕西省西安市城南的曲江开发区，是中国第一个全方位展示盛唐风貌的大型皇家园林式文化主题公园。";
	G.S[5].rank = 5;
	G.S[5].price = 0;
	G.S[6].num = 7;
	G.S[6].name = "永兴坊";
	G.S[6].introduction = "永兴坊汇集了陕西各地特色美食经营户五十余家，有省级非物质文化遗产美食，市级非物质文化遗产美食 ，还有手工民俗技艺表演及各地名小吃。";
	G.S[6].rank = 1;
	G.S[6].price = 0;
	G.S[7].num = 8;
	G.S[7].name = "回民街";
	G.S[7].introduction = "西安回民街作为西安风情的代表之一，是回民街区多条街道的统称，由北广济街、北院门、西羊市、大皮院、化觉巷、洒金桥等数条街道组成，在钟鼓楼后。";
	G.S[7].rank = 1;
	G.S[7].price = 0;
	G.S[8].num = 9;
	G.S[8].name = "洒金桥";
	G.S[8].introduction = "洒金桥位于陕西省西安市莲湖区的回坊内，北起莲湖路南至新寺巷，全长800米。";
	G.S[8].rank = 1;
	G.S[8].price = 0;
	G.S[9].num = 10;
	G.S[9].name = "小雁塔";
	G.S[9].introduction = "小雁塔，位于唐长安城安仁坊（今陕西省西安市南郊）荐福寺内，又称“荐福寺塔”，建于唐景龙年间，与大雁塔同为唐长安城保留至今的重要标志。";
	G.S[9].rank = 4;
	G.S[9].price = 0;
	G.S[10].num = 11;
	G.S[10].name = "大唐西市";
	G.S[10].introduction = "大唐西市唐朝长安城两大市场（东市和西市）之一，被誉为“金市”，是当时世界上最大的商贸中心。";
	G.S[10].rank = 4;
	G.S[10].price = 0;
	G.S[11].num = 12;
	G.S[11].name = "阿房宫遗址";
	G.S[11].introduction = "位于陕西省西安市西咸新区阿房村 ，始建于秦始皇三十五年，后因秦朝灭亡，阿房宫并未完全建成 。";
	G.S[11].rank = 5;
	G.S[11].price = 38;
	G.S[12].num = 13;
	G.S[12].name = "青龙寺";
	G.S[12].introduction = "佛教八大宗派之一密宗祖庭，唐朝佛教真言宗祖庭。";
	G.S[12].rank = 3;
	G.S[12].price = 0;
	G.S[13].num = 14;
	G.S[13].name = "西安碑林博物馆";
	G.S[13].introduction = "陕西创建最早的博物馆，它以收藏、陈列和研究历代碑刻、墓志及石刻为主，成为在中国独树一帜的艺术博物馆。";
	G.S[13].rank = 5;
	G.S[13].price = 60;
	G.S[14].num = 15;
	G.S[14].name = "陕西历史博物馆";
	G.S[14].introduction = "陕西历史博物馆，中国第一座大型现代化国家级博物馆，首批“AAAA”级旅游景点，被誉为“古都明珠，华夏宝库”。";
	G.S[14].rank = 4;
	G.S[14].price = 0;
	G.S[15].num = 16;
	G.S[15].name = " 曲江海洋极地公园";
	G.S[15].introduction = "西安曲江海洋极地公园是由西安曲江文旅集团投资开发，是我国西部地区规模最大的大型海洋主题公园，其规模及展示水平可跻身国内海洋馆前五位。";
	G.S[15].rank = 4;
	G.S[15].price = 150;
	G.S[16].num = 17;
	G.S[16].name = "白鹿原·白鹿仓";
	G.S[16].introduction = "白鹿原·白鹿仓景区是由陕西锋双集团投资建设，于上风上水之地打造的全域旅游战略旗舰项目，被誉为推进全域旅游发展示范单位。";
	G.S[16].rank = 4;
	G.S[16].price = 0;
	G.S[17].num = 18;
	G.S[17].name = "青曲社";
	G.S[17].introduction = "青曲社 是位于陕西省西安市的一个相声社团 ，成立于2007年。社团名称蕴含“青云直上，曲故情长”的意思。";
	G.S[17].rank = 2;
	G.S[17].price = 200;
	G.S[18].num = 19;
	G.S[18].name = "西安半坡遗址";
	G.S[18].introduction = "半坡遗址是新石器时代仰韶文化聚落遗址，年代为中国原始社会母系氏族繁荣时期遗留下的村落遗址。";
	G.S[18].rank = 4;
	G.S[18].price = 50;
	G.S[19].num = 20;
	G.S[19].name = "中国唐苑";
	G.S[19].introduction = "中国唐苑以盆景艺术享誉海内外。盆景艺术起源于唐代，而且深受皇家的青睐。";
	G.S[19].rank = 4;
	G.S[19].price = 0;
	G.S[20].num = 21;
	G.S[20].name = "西安世博园";
	G.S[20].introduction = "西安世博园，原名西安世园公园，又称西安世园会，位于西安市浐灞生态区广运潭。";
	G.S[20].rank = 4;
	G.S[20].price = 0;
	G.S[21].num = 22;
	G.S[21].name = "秦始皇帝陵博物院";
	G.S[21].introduction = "秦始皇帝陵博物院位于陕西省西安市临潼区，是以秦始皇兵马俑博物馆为基础，以秦始皇帝陵遗址公园为依托的一座大型遗址博物院。";
	G.S[21].rank = 5;
	G.S[21].price = 120;
	G.S[22].num = 23;
	G.S[22].name = "华清池景区";
	G.S[22].introduction = "位于陕西省西安市临潼区城南，是秦岭山脉的一个支脉。";
	G.S[22].rank = 5;
	G.S[22].price = 120;
	G.S[23].num = 24;
	G.S[23].name = "终南山·南五台景区";
	G.S[23].introduction = "南五台是终南山国家森林公园的主要景区，也是省级风景名胜区。";
	G.S[23].rank = 3;
	G.S[23].price = 40;
	G.S[24].num = 25;
	G.S[24].name = " 翠华山";
	G.S[24].introduction = "翠华山原名太乙山，景区由碧山湖景区、天池景区和山崩石海景区3部分组成。传说有太乙真人在此修炼过，由此得名。";
	G.S[24].rank = 4;
	G.S[24].price = 40;
	G.S[25].num = 26;
	G.S[25].name = " 乐华恒业欢乐世界";
	G.S[25].introduction = "西安乐华欢乐世界是亚洲超大主题乐园，为国家AAAA级旅游景区。";
	G.S[25].rank = 4;
	G.S[25].price = 250;
	G.S[26].num = 27;
	G.S[26].name = "秦岭野生动物园";
	G.S[26].introduction = "西安秦岭野生动物园，是集野生动物移地保护、科普教育、旅游观光、休闲度假于一体的国家4A级旅游景区。";
	G.S[26].rank = 4;
	G.S[26].price = 100;
	G.S[27].num = 28;
	G.S[27].name = "古观音禅寺";
	G.S[27].introduction = "古观音禅寺位于陕西省西安市长安区东大街办罗汉洞村，始建于唐贞观二年，距今约有1400年历史，为终南山千年古刹之一。";
	G.S[27].rank = 3;
	G.S[27].price = 0;
	G.S[28].num = 29;
	G.S[28].name = "西北工业大学长安校区";
	G.S[28].introduction = "西北工业大学长安校区位于西安市长安区境内秦岭北麓下，按照现代化、数字化、山水园林式生态型的一流大学校园进行规划和建设，努力构筑具有西工大特色的校园景观。";
	G.S[28].rank = 2;
	G.S[28].price = 0;
	G.S[29].num = 30;
	G.S[29].name = "西安电子科技大学南校区";
	G.S[29].introduction = "西安电子科技大学新校区位于西安市长安区壮丽的秦岭北麓，占地3000余亩。";
	G.S[29].rank = 2;
	G.S[29].price = 0;
	G.S[30].num = 31;
	G.S[30].name = "诗经里";
	G.S[30].introduction = "诗经里是全国首个诗经主题特色小镇，位于陕西省西安市沣河之滨。";
	G.S[30].rank = 2;
	G.S[30].price = 0;
	G.S[31].num = 32;
	G.S[31].name = "昆明池·七夕公园";
	G.S[31].introduction = "七夕公园在我国开凿于公元前120年的历史上第一个人工蓄水工程昆明池的基础上建成，位于陕西省西安市西南。";
	G.S[31].rank = 4;
	G.S[31].price = 0;
	G.S[32].num = 33;
	G.S[32].name = "华夏文旅海洋公园";
	G.S[32].introduction = "西安华夏文旅海洋公园，是一座少有的海洋文化和当地民俗相融合，生动展现全球各地海洋文化的大型综合性海洋场馆，是中国较大的民俗海洋馆。";
	G.S[32].rank = 3;
	G.S[32].price = 180;
	G.S[33].num = 34;
	G.S[33].name = "清凉山森林公园";
	G.S[33].introduction = "西安清凉山公园位于西安市长安区上塔坡村凤栖塬，根据规划，将形成“一轴、五区、六点”的景观布局。";
	G.S[33].rank = 3;
	G.S[33].price = 0;
	G.S[34].num = 35;
	G.S[34].name = " 西安植物园";
	G.S[34].introduction = "陕西省西安植物园，是一所以植物科学研究、植物种质资源收集保存、植物科学普及为核心定位，集公众休憩游览、环保科普、城市生态与减灾避险等社会功能为一体的综合性省级科研机构。";
	G.S[34].rank = 3;
	G.S[34].price = 10;
	G.S[35].num = 36;
	G.S[35].name = "曲江池遗址公园";
	G.S[35].introduction = "曲江池遗址公园，北接大唐芙蓉园，南至秦二世陵遗址。";
	G.S[35].rank = 3;
	G.S[35].price = 0;
	G.S[36].num = 37;
	G.S[36].name = "城市运动公园";
	G.S[36].introduction = "西安城市运动公园位于西安北城经济开发区中心位置，亚洲首屈一指的主题公园。";
	G.S[36].rank = 2;
	G.S[36].price = 30;
	G.S[37].num = 38;
	G.S[37].name = " 兴庆宫公园";
	G.S[37].introduction = "兴庆宫公园是中国最古老的历史文化遗址公园，与百年名校西安交通大学相邻。";
	G.S[37].rank = 1;
	G.S[37].price = 0;
	G.S[38].num = 39;
	G.S[38].name = "浐灞桃花潭公园";
	G.S[38].introduction = "公园地形多样，依山傍水，自然环境优美，是浐灞河综合治理工程的重要亮点。";
	G.S[38].rank = 3;
	G.S[38].price = 0;
	G.S[39].num = 40;
	G.S[39].name = "西安建筑科技大学草堂校区";
	G.S[39].introduction = "西安建筑科技大学草堂校区位于秦岭北麓生态旅游观光带及关中环线环山公路上。";
	G.S[39].rank = 3;
	G.S[39].price = 0;
	for (int i = 0; i < 40; i++)
	{
		SubG.S[i].num = BusG.S[i].num = BikeG.S[i].num = TaxiG.S[i].num = G.S[i].num;
		SubG.S[i].name = G.S[i].name;
		BusG.S[i].name =G.S[i].name;
		BikeG.S[i].name = G.S[i].name;
		TaxiG.S[i].name = G.S[i].name;
	}
};
void Graph::Creat_maps()
{
	int i, j;
	G.n = 40;//40个景点
	G.m = 51;//49条双向路径
	for (i = 0; i < G.n; i++)
	{
		for (j = 0; j < G.n; j++)
		{
			if (i == j)
			{
				G.P[i][j].dis = 0;
			}
			else
			{
				G.P[i][j].dis = MAX;
			}
		}
	}
	G.P[0][2].dis = G.P[2][0].dis = 4;
	G.P[0][38].dis = G.P[38][0].dis = 8;
	G.P[1][0].dis = G.P[0][1].dis = 7;
	G.P[2][36].dis = G.P[36][2].dis = 11;
	G.P[1][13].dis = G.P[13][1].dis = 2;
	G.P[1][7].dis = G.P[7][1].dis = 1;
	G.P[3][4].dis = G.P[4][3].dis = 1;
	G.P[3][5].dis = G.P[5][3].dis = 1;
	G.P[4][12].dis = G.P[12][4].dis = 4;
	G.P[4][14].dis = G.P[14][4].dis = 5;
	G.P[5][15].dis = G.P[15][5].dis = 1;
	G.P[15][35].dis = G.P[35][15].dis = 1;
	G.P[6][13].dis = G.P[13][6].dis = 3;
	G.P[6][37].dis = G.P[37][6].dis = 3;
	G.P[7][8].dis = G.P[8][7].dis = 3;
	G.P[7][17].dis = G.P[17][7].dis = 1;
	G.P[8][10].dis = G.P[10][8].dis = 4;
	G.P[9][10].dis = G.P[10][9].dis = 4;
	G.P[9][13].dis = G.P[13][9].dis = 3;
	G.P[9][14].dis = G.P[14][9].dis = 4;
	G.P[9][17].dis = G.P[17][9].dis = 3;
	G.P[10][11].dis = G.P[11][10].dis = 9;
	G.P[10][33].dis = G.P[33][10].dis = 9;
	G.P[11][30].dis = G.P[30][11].dis = 9;
	G.P[12][15].dis = G.P[15][12].dis = 5;
	G.P[12][37].dis = G.P[37][12].dis = 2;
	G.P[12][13].dis = G.P[13][12].dis = 4;
	G.P[14][26].dis = G.P[26][14].dis = 25;
	G.P[15][34].dis = G.P[34][15].dis = 5;
	G.P[16][19].dis = G.P[19][16].dis = 17;
	G.P[18][37].dis = G.P[37][18].dis = 9;
	G.P[18][38].dis = G.P[38][18].dis = 6;
	G.P[19][34].dis = G.P[34][19].dis = 3;
	G.P[19][35].dis = G.P[35][19].dis = 6;
	G.P[20][22].dis = G.P[22][20].dis = 20;
	G.P[20][32].dis = G.P[32][20].dis = 5;
	G.P[20][38].dis = G.P[38][20].dis = 4;
	G.P[21][22].dis = G.P[21][22].dis = 1;
	G.P[23][24].dis = G.P[24][23].dis = 13;
	G.P[23][26].dis = G.P[26][23].dis = 14;
	G.P[25][36].dis = G.P[36][25].dis = 20;
	G.P[26][27].dis = G.P[27][26].dis = 8;
	G.P[27][28].dis = G.P[28][27].dis = 4;
	G.P[28][29].dis = G.P[29][28].dis = 14;
	G.P[28][39].dis = G.P[39][28].dis = 2;
	G.P[29][33].dis = G.P[33][29].dis = 12;
	G.P[29][31].dis = G.P[31][29].dis = 17;
	G.P[30][31].dis = G.P[31][30].dis = 5;
	G.P[32][36].dis = G.P[36][32].dis = 9;
	G.P[32][38].dis = G.P[38][32].dis = 6;
	//计算顶点的度
	int degree;
	for (i = 0; i < G.n; i++)
	{
		degree = 0;
		for (j = 0; j < G.n; j++)
		{
			if (i != j && G.P[i][j].dis < MAX)
			{
				degree++;
			}
		}
		G.S[i].degree = degree;
	}
	//根据度计算路径拥堵程度
	for (i = 0; i < G.n; i++)
	{
		for (j = 0; j < G.n; j++)
		{
			G.P[i][j].state = -1;
			if (i != j && G.P[i][j].dis < MAX)
			{
				if ((G.S[i].degree + G.S[j].degree) / 2.0 >= 3)
				{
					G.P[i][j].state = 1;
				}
				else
				{
					G.P[i][j].state = 0;
				}
			}
		}
	}
	//生成地铁路径图
	SubG.n = 20, SubG.m = 40;
	for (i = 0; i < SubG.n; i++)
	{
		for (j = 0; j < SubG.n; j++)
		{
			SubG.P[i][j].dis = G.P[i][j].dis;
			if (i != j && G.P[i][j].dis < MAX)
			{
				SubG.P[i][j].dis = G.P[i][j].dis / 4.0;
			}
		}
	}
	SubG.P[19][35].dis = SubG.P[35][19].dis = MAX;
	SubG.P[12][15].dis = SubG.P[15][12].dis = MAX;
	SubG.P[4][14].dis = SubG.P[14][4].dis = MAX;
	SubG.P[6][37].dis = SubG.P[37][6].dis = MAX;
	SubG.P[6][13].dis = SubG.P[13][6].dis = MAX;
	SubG.P[20][32].dis = SubG.P[32][20].dis = MAX;
	SubG.P[25][36].dis = SubG.P[36][25].dis = MAX;
	SubG.P[7][8].dis = SubG.P[8][7].dis = MAX;
	SubG.P[8][10].dis = SubG.P[10][8].dis = MAX;
	SubG.P[10][33].dis = SubG.P[33][10].dis = MAX;
	SubG.P[26][33].dis = SubG.P[33][26].dis = MAX;
	SubG.P[29][33].dis = SubG.P[33][29].dis = MAX;
	SubG.P[26][27].dis = SubG.P[27][26].dis = MAX;
	SubG.P[27][28].dis = SubG.P[28][27].dis = MAX;
	//生成公交路径图
	BusG.n = 20, BusG.m = 40;
	for (i = 0; i < BusG.n; i++)
	{
		for (j = 0; j < BusG.n; j++)
		{
			BusG.P[i][j].dis = G.P[i][j].dis;
			if (i != j && G.P[i][j].dis < MAX)
			{
				if (G.P[i][j].state == 1)
				{
					BusG.P[i][j].dis = G.P[i][j].dis * 1.5;
				}
				else
				{
					BusG.P[i][j].dis = G.P[i][j].dis / 2.2;
				}
			}
		}
	}
	BusG.P[32][36].dis = BusG.P[36][32].dis = MAX;
	BusG.P[20][38].dis = BusG.P[38][20].dis = MAX;
	BusG.P[0][38].dis = BusG.P[38][0].dis = MAX;
	BusG.P[12][37].dis = BusG.P[37][12].dis = MAX;
	BusG.P[10][9].dis = BusG.P[9][10].dis = MAX;
	BusG.P[10][33].dis = BusG.P[33][10].dis = MAX;
	BusG.P[4][12].dis = BusG.P[12][4].dis = MAX;
	BusG.P[19][35].dis = BusG.P[35][19].dis = MAX;
	//生成自行车路径图
	BikeG.m = 20, BikeG.n = 40;
	for (i = 0; i < BikeG.n; i++)
	{
		for (j = 0; j < BikeG.n; j++)
		{
			BikeG.P[i][j].dis = G.P[i][j].dis;
			if (i != j && G.P[i][j].dis < MAX)
			{
				BikeG.P[i][j].dis = G.P[i][j].dis / 1.1;
			}
		}
	}
	//生成出租车路径图
	TaxiG.m = 20, TaxiG.n = 40;
	for (i = 0; i < TaxiG.n; i++)
	{
		for (j = 0; j < TaxiG.n; j++)
		{
			TaxiG.P[i][j].dis = G.P[i][j].dis;
			if (i != j && G.P[i][j].dis < MAX)
			{
				if (G.P[i][j].state == 1)
				{
					TaxiG.P[i][j].dis = G.P[i][j].dis * 1.2;
				}
				else
				{
					TaxiG.P[i][j].dis = G.P[i][j].dis / 2.5;
				}
			}
		}
	}


	//0为人行道，1为车行道，2为都可
	G.P[0][2].pathtype = G.P[2][0].pathtype = 2;
	G.P[12][13].pathtype = G.P[13][12].pathtype = 2;
	G.P[0][38].pathtype = G.P[38][0].pathtype = 2;
	G.P[1][0].pathtype = G.P[0][1].pathtype = 2;
	G.P[2][36].pathtype = G.P[36][2].pathtype = 2;
	G.P[1][13].pathtype = G.P[13][1].pathtype = 1;
	G.P[1][7].pathtype = G.P[7][1].pathtype = 2;
	G.P[3][4].pathtype = G.P[4][3].pathtype = 0;
	G.P[3][5].pathtype = G.P[5][3].pathtype = 2;
	G.P[4][12].pathtype = G.P[12][4].pathtype = 2;
	G.P[4][14].pathtype = G.P[14][4].pathtype = 2;
	G.P[5][15].pathtype = G.P[15][5].pathtype = 0;
	G.P[15][35].pathtype = G.P[35][15].pathtype = 2;
	G.P[6][13].pathtype = G.P[13][6].pathtype = 2;
	G.P[6][37].pathtype = G.P[37][6].pathtype = 2;
	G.P[7][8].pathtype = G.P[8][7].pathtype = 2;
	G.P[7][17].pathtype = G.P[17][7].pathtype = 0;
	G.P[8][10].pathtype = G.P[10][8].pathtype = 1;
	G.P[9][10].pathtype = G.P[10][9].pathtype = 2;
	G.P[9][13].pathtype = G.P[13][9].pathtype = 2;
	G.P[9][14].pathtype = G.P[14][9].pathtype = 1;
	G.P[9][17].pathtype = G.P[17][9].pathtype = 2;
	G.P[10][11].pathtype = G.P[11][10].pathtype = 2;
	G.P[10][33].pathtype = G.P[33][10].pathtype = 0;
	G.P[11][30].pathtype = G.P[30][11].pathtype = 2;
	G.P[12][15].pathtype = G.P[15][12].pathtype = 2;
	G.P[12][37].pathtype = G.P[37][12].pathtype = 2;
	G.P[14][26].pathtype = G.P[26][14].pathtype = 2;
	G.P[15][34].pathtype = G.P[34][15].pathtype = 2;
	G.P[16][19].pathtype = G.P[19][16].pathtype = 2;
	G.P[18][37].pathtype = G.P[37][18].pathtype = 0;
	G.P[18][38].pathtype = G.P[38][18].pathtype = 2;
	G.P[19][34].pathtype = G.P[34][19].pathtype = 2;
	G.P[19][35].pathtype = G.P[35][19].pathtype = 1;
	G.P[20][22].pathtype = G.P[22][20].pathtype = 2;
	G.P[20][32].pathtype = G.P[32][20].pathtype = 1;
	G.P[20][38].pathtype = G.P[38][20].pathtype = 2;
	G.P[21][22].pathtype = G.P[21][22].pathtype = 2;
	G.P[23][24].pathtype = G.P[24][23].pathtype = 2;
	G.P[23][26].pathtype = G.P[26][23].pathtype = 2;
	G.P[25][36].pathtype = G.P[36][25].pathtype = 2;
	G.P[26][27].pathtype = G.P[27][26].pathtype = 2;
	G.P[26][33].pathtype = G.P[33][26].pathtype = 1;
	G.P[27][28].pathtype = G.P[28][27].pathtype = 0;
	G.P[28][29].pathtype = G.P[29][28].pathtype = 2;
	G.P[28][39].pathtype = G.P[39][28].pathtype = 2;
	G.P[29][33].pathtype = G.P[33][29].pathtype = 2;
	G.P[29][31].pathtype = G.P[31][29].pathtype = 2;
	G.P[30][31].pathtype = G.P[31][30].pathtype = 2;
	G.P[32][36].pathtype = G.P[36][32].pathtype = 0;
	G.P[32][38].pathtype = G.P[38][32].pathtype = 1;

}
