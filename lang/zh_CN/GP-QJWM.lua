-- QianJunWanMa Shuihusha part 1. code by: UbunTenkei

return {
	["QJWM"] = "千军万马",

	["#liying"] = "扑天雕",
	["liying"] = "李应",
	["cv:liying"] = "烨子【剪刀剧团】",
	["kong1iang"] = "控粮",
	[":kong1iang"] = "摸牌阶段，你可以摸X张牌，X为你的体力上限与你已损失的体力值之和，若如此做，你须展示你的手牌，弃置其中任意两种花色的所有牌（不足则全弃）。",
	["#Kongrice"] = "%from 弃置了自己 %arg 花色的所有牌",
	["$kong1iang1"] = "大军未动，粮草先行！",
	["$kong1iang2"] = "粮草器械，尽在掌控之中。",

	["#shijin"] = "九纹龙",
	["shijin"] = "史进",
	["wubang"] = "舞棒",
	["cv:shijin"] = "烨子【剪刀剧团】",
	[":wubang"] = "其他角色的武器牌进入弃牌堆时，你可以获得之。",
	["xiagu"] = "侠骨",
	[":xiagu"] = "任意角色受到无属性伤害时，你可以弃置一张装备牌，令该伤害-1.",
	["@xiagu"] = "你可以弃置一张装备牌发动【侠骨】（令该伤害-1）",
	["$Xiagu"] = "%from 发动了【侠骨】，弃置了 %card，令 %to 受到的伤害 -1",
	["$wubang1"] = "哪位教头再来点拨？",
	["$wubang2"] = "看我耍枪弄棒！",
	["$xiagu1"] = "大郎在此，这厮休得无礼。",
	["$xiagu2"] = "诸位哥哥，小弟来挡！",

	["#zhuwu"] = "神机军师",
	["zhuwu"] = "朱武",
	["pozhen"] = "破阵",
	["cv:zhuwu"] = "烨子【剪刀剧团】",
	[":pozhen"] = "<b>锁定技</b>，你使用的非延时类锦囊不能被【无懈可击】或【将计就计】响应。",
	["#Pozhen"] = "%from 的锁定技【%arg】被触发，使用的这张 %arg2 不能被【无懈可击】或【将计就计】抵消",
	["buzhen"] = "布阵",
	[":buzhen"] = "<font color=purple><b>限定技</b></font>，你可以跳过你的出牌阶段，交换任意两名角色的位置。",
	["@buvr"] = "布阵",
	["@buzhen"] = "你可以选择两名角色发动【布阵】（交换他们的位置）",
	["fangzhen"] = "方阵",
	[":fangzhen"] = "<b>锁定技</b>，你不能成为体力比你多的角色使用【杀】或【决斗】的目标。",
	["$pozhen1"] = "洞察先机，无有不破！",
	["$pozhen2"] = "意志被摧毁了吗？",
	["$buzhen"] = "汝当作先锋，汝可为接应，大军严守生门，此战可定也！",
	["$Buzhen"] = "汝当作先锋，\
汝可为接应，\
大军严守生门，\
此战可定也！",

	["#hantao"] = "百胜将",
	["hantao"] = "韩滔",
	["taolue"] = "韬略",
	["cv:hantao"] = "猎狐【声声melody】",
	[":taolue"] = "出牌阶段，你可以和一名角色拼点。若你赢，你可以将该角色判定区或装备区里的一张牌移到另一个合理的位置。若你没赢，你须弃置一张牌。每回合限一次。",
	["changsheng"] = "常胜",
	[":changsheng"] = "<b>锁定技</b>，你拼点的黑桃牌点数都视为K。",
	["#Changsheng"] = "%from 的锁定技【%arg】被触发，%from 拼点牌的点数视为K",
	["$changsheng1"] = "进可攻，退可守！",
	["$changsheng2"] = "流水无形而无不形。",
	["$taolue1"] = "斩杀敌将，犹如儿戏！",
	["$taolue2"] = "人上有人，天外有天。",

	["#oupeng"] = "摩云金翅",
	["oupeng"] = "欧鹏",
	["zhanchi"] = "展翅",
	["designer:oupeng"] = "烨子&凌天翼",
	["cv:oupeng"] = "烨子【剪刀剧团】",
	[":zhanchi"] = "<font color=purple><b>限定技</b></font>，你可以跳过你的判定阶段并弃掉你判定区里的所有牌，永久获得技能“腾飞”（<b>锁定技</b>，回合结束时，你须减1点体力上限，进行一个额外的回合；你的攻击范围与你的当前体力值相等）。",
	["@vfui"] = "展翅",
	["tengfei"] = "腾飞",
	[":tengfei"] = "<b>锁定技</b>，回合结束时，你须减1点体力上限，进行一个额外的回合；你的攻击范围等于你的当前体力值。",
	["#Tengfei"] = "%from 的锁定技【%arg】被触发，将进行一个额外的回合",
	["$zhanchi"] = "迦楼罗，重生！",
	["$tengfei1"] = "我要飞得更高！",
	["$tengfei2"] = "以吾之血，毕其功于一役！",

	["#shien"] = "金眼彪",
	["shien"] = "施恩",
	["cv:shien"] = "明哲【剪刀剧团】",
	["longluo"] = "笼络",
	[":longluo"] = "当你成为【杀】的目标时，你可以亮出牌堆顶的两张牌，将其中的基本牌以任意分配方式交给任意角色并弃置其余的牌。",
	["$Longluo1"] = "%from 亮出的 %card 不是基本牌，自动弃置",
	["$Longluo2"] = "%from 亮出的 %card 是基本牌，可以交给任意一名角色",
	["xiaozai"] = "消灾",
	[":xiaozai"] = "每当你受到伤害时，可以交给任一除伤害来源外的其他角色两张手牌，将该伤害转移给该角色。",
	["@xiaozai"] = "你可以交给除你和伤害来源外的一名角色两张手牌，将该伤害转移给该角色",
	["$longluo1"] = "小小心意，不成敬意。",
	["$longluo2"] = "好汉，且慢！",
	["$xiaozai1"] = "上下使得银两，可免三百杀威棒！",
	["$xiaozai2"] = "财可通神，只当破财消灾。",

	["#luozhenren"] = "半仙",
	["luozhenren"] = "罗真人",
	["cv:luozhenren"] = "东方胤弘【夜澜锦音】",
	["butian"] = "卜天",
	[":butian"] = "在任意角色的判定牌生效前，你可以弃置一张牌，观看牌堆顶的三张牌，将其中的任意一张牌与该判定牌进行交换。",
	["@butian-card"] = "请弃置一张牌，发动技能【卜天】（更改 %src 的 %arg 判定结果）",
	["huaxian"] = "化仙",
	[":huaxian"] = "当你进入濒死状态时，可以进行一次判定：若结果为红桃，你回复1点体力。",
	["$butian1"] = "掐指一算，万事尽知。",
	["$butian2"] = "天道？哈哈哈～",
	["$huaxian1"] = "脚著谢公屐，身登青云梯。",
	["$huaxian2"] = "天劫已度，上可登仙。",

-- last words
	["~liying"] = "兵粮寸断，以何取胜？！",
	["~shijin"] = "何以别离久，何以不得安。",
	["~zhuwu"] = "生门已破，此战败也。",
	["~hantao"] = "终究还是败了。",
	["~oupeng"] = "呃～啊！连珠箭！",
	["~shien"] = "唉，散尽钱财，亦不能避祸，都不是等闲之辈啊！",
	["~luozhenren"] = "灾祸易躲，天命难违。",
}
