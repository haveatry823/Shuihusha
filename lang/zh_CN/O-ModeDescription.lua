-- The translate for description of modes

return {
	[":02p"] = "两人局\
1主公、1反贼，一局定胜负，首先阵亡的角色宣告败北。",
	[":02_1v1"] = "标准1v1模式\
1主公、1内奸，每名玩家选出三名武将出战，首先三名武将全部阵亡的玩家宣告败北。",
	[":03p"] = "三人局\
1主公、1反贼、1内奸。",
	[":04p"] = "四人局\
1主公、2反贼、1内奸。",
	[":05p"] = "五人局\
1主公、1忠臣、2反贼、1内奸。",
	[":06p"] = "六人局\
1主公、1忠臣、3反贼、1内奸",
	[":06pd"] = "六人局（双内）\
1主公、1忠臣、2反贼、2内奸。",
	[":06_3v3"] = "标准3v3模式\
1暖色主帅、2暖色边锋、1冷色主帅、2冷色边锋，冷暖双方交替行动，主帅首先阵亡的一方宣告败北。\
★该模式中使用【猛虎下山】、【万箭齐发】、【梁山聚义】、【五谷丰登】及【逢凶化吉】时可指定顺时针或逆时针的结算方向。\
★原则上不加入“天灾牌”，如：【闪电】、【海啸】及【生辰纲】等。",
	[":07p"] = "七人局\
1主公、2忠臣、3反贼、1内奸。",
	[":08p"] = "八人局\
1主公、2忠臣、4反贼、1内奸。",
	[":08pd"] = "八人局（双内）\
1主公、2忠臣、3反贼、2内奸。",
	[":08pz"] = "八人局（无内）\
1主公、3忠臣、4反贼。",
	[":09p"] = "九人局\
1主公、3忠臣、4反贼、1内奸。",
	[":10pd"] = "十人局（双内）\
1主公、3忠臣、4反贼、2内奸。",
	[":10p"] = "十人局\
1主公、3忠臣、5反贼、1内奸。",
	[":10pz"] = "十人局（无内）\
1主公、4忠臣、5反贼。",
	[":12p"] = "十二人局",

	[":arthur_ferris"] = "杀上保下模式\
当一名玩家阵亡后，他/她的下家宣告胜利。\
“杀上保下”不仅是一个非常讲究游戏策略的模式，同时也是一个极为残酷的杀人游戏，当你要保护的人成为杀你的凶手时，你心里又在作何感想呢？",
	[":couple"] = "花田错模式\
最后存活的一对夫妇宣告胜利（若其中一名角色已阵亡，则与其存活的配偶宣告共同胜利）。\
模式来源于“周通抢亲”桥段。这个世界上，对的时间，遇见错的人，错的时间，遇见对的人，这全是玩弄人的把戏。唯有我配得上你，也唯有你配得上我，只有你和我永远在一起，方为真爱。\
★当一名存活的女性武将的配偶阵亡后，若周通为单身状态，则周通强制与其结姻。",
	[":dusong"] = "独松关模式\
由三名玩家组成联合军，对抗另一名玩家“张清&董平”，双方对抗，最后存活的一方宣告胜利。\
东昌马骑将，没羽箭张清。英雄双枪将，风流万户侯。英雄惜英雄，奈何唯气短。英魂常常驻，永垂独松关！\
★模式中玩家可以将武器牌置入弃牌堆，然后摸一张牌。\
★当“张清&董平”的体力值为4或更低时，当前玩家的回合立即终止，“张清&董平”进入第二阶段，弃置其判定区里的所有牌，并将其武器牌重置之。",
	[":endless"] = "无尽模式\
当洗牌次数达到启动服务器时设定好的次数后，场上拥有“铜板”最多的玩家宣告胜利，若有并列者，则宣告共同胜利。\
英雄厮杀，一战到天明，英雄孤寂，唯有无止境的战斗，方可安其心，振其势。\
★你造成伤害后，可以获得等同于该伤害值数量的“铜板”；当你受到无来源的伤害或流失体力后，获得等同于该伤害值（流失体力值）数量的“铜板”；当其他角色因你进入死亡临界状态时，你获得其一半的“铜板”（向下取整）。",
	[":hegemony"] = "国战模式\
当场上所有玩家均亮明武将，且均为同一势力时，游戏结束，该势力的所有亮明武将的玩家宣告胜利（若有角色已阵亡，则宣告共同胜利）。\
硝烟再次点燃，风云变幻际会，每一颗期盼的心在等待这一刻的来临，手中的武器已经准备就绪，荣誉的征战即将来临，为了国家的荣耀，心中的信念时刻在敲打着我们，胜利，是你我唯一的目标。\
★场上若已有两名同势力的玩家亮明武将，则其他该势力的暗将不可亮明武将。",
	[":landlord"] = "斗地主模式\
模式来源于传统卡牌游戏“斗地主”和“挖坑”，以3人单将身份局为基本环境，衍生出的一个富有乐趣的竞技型模式。\
地主逼佃农，佃农斗地主，哪里有压迫，哪里就有反抗。揭竿而起的时候到了！\
★当一名佃农死亡后，地主减1点体力上限。\
★禁用转世规则及暗将规则。\
★地主拥有一个随机的地主技（详见扩展模式“斗地主”规则介绍）。",
	[":warlords"] = "投名状模式\
游戏开始时，所有的玩家身份均为“草寇”，需要不断取人头，改变身份和命运，获得最终的胜利。当所有草寇均阵亡后，寨主（和军师）宣告胜利。\
欲上梁山，须交出投名状，不是一纸一金，是人头。可这一洼之水，一山小寨，又如何容得许多真龙？\
★杀死“军师”的“草寇”变为“军师”；杀死“寨主”的“草寇”变为“寨主”，并可根据“血”标记数选择另一名玩家与当前“军师”互换身份。\
★当一名玩家阵亡后，若场上无“寨主”，则会随机选出一名玩家作为“寨主”。",
	[":wheel_fight"] = "车轮战模式\
2人进行对战，当一名武将阵亡后，玩家可以更换武将继续作战，直到满足启动服务器时设定的条件（最大阵亡次数）为止，此时，阵亡次数最少的玩家宣告胜利。\
己方分散兵力，轮流与敌人作战，可采取迂回战术，在体力和智力上使敌人倦怠，趁虚而入，杀他个片甲不留。\
★当一名武将连续杀死对方三次，则玩家须更换武将。\
★更换武将时，须弃置所有牌，然后摸3-4张牌。",
}