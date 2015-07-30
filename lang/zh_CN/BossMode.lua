-- translation for Boss Mode

return {
	["BossMode"] = "闯关模式",
	["#BossTurnCount"] = "%from 的第 %arg 回合开始",

	["bossqichang"] = "气场",
	[":bossqichang"] = "锁定技。回合开始前，若你背面朝上，将你的人物牌翻面；若你的正面朝上，弃置判定区内的牌。你的体力上限变化时，取消之。",
	["bossfuckyourdoublegenerals"] = "去死吧！双将魂淡！",
	[":bossfuckyourdoublegenerals"] = "锁定技。双将的角色对你造成的伤害/2（向上取整），你对双将的角色造成双倍伤害。",

	["#boss_yuuki"] = "Boss Lv.1",
	["Yuuki"] = "优纪",
	["bossduel"] = "对决",
	[":bossduel"] = "游戏开始时和你的回合准备阶段开始时，你可以令两名角色翻面。",
	["bossjuejian"] = "绝剑",
	[":bossjuejian"] = "锁定技，每当你闪避一张【杀】时，视为你对所有角色使用一张【杀】。",
	["bossmothersrosario"] = "圣母咏叹",
	[":bossmothersrosario"] = "你进入濒死阶段时，视为对一名角色使用【杀】【过河拆桥】【杀】【顺手牵羊】【决斗】【火杀】【雷杀】【过河拆桥】【决斗】【杀】【杀】，然后你立即死亡。",

	["#boss_heathcliff"] = "Boss Lv.1",
	["Heathcliff"] = "希斯克利夫",
	["bossholyshield"] = "神圣盾",
	[":bossholyshield"] = "锁定技，其他角色对你使用的【杀】有85%的概率无效化，然后你对来源造成一点伤害。",
	["bossgm"] = "GM",
	[":bossgm"] = "当你的体力值变化可以令你体力值小于50%时，你可以取消之并将体力设为50%，失去该技能，然后指定一名角色并封锁其他角色的基本牌，非基本牌和技能直到你死亡。",

	["#boss_niutou"] = "Boss Lv.2",
	["boss_niutou"] = "牛头",
	["bossbaolian"] = "暴敛",
	[":bossbaolian"] = "锁定技。结束阶段开始时，你摸两张牌。",
	["bossmanjia"] = "蛮甲",
	[":bossmanjia"] = "锁定技。若你的装备区没有防具牌，视为你装备【藤甲】。",
	["bossxiaoshou"] = "枭首",
	[":bossxiaoshou"] = "结束阶段开始时，你可以对一名体力值大于你的角色造成2点伤害。",
	["bossxiaoshou-invoke"] = "你可以发动“枭首”<br/> <b>操作提示</b>: 选择一名体力值大于你的角色→点击确定<br/>",

	["#boss_mamian"] = "Boss Lv.2",
	["boss_mamian"] = "马面",
	["bossguiji"] = "诡计",
	[":bossguiji"] = "锁定技。准备阶段结束时，若你的判定区有牌，随机弃置其中一张。",
	["bosslianyu"] = "炼狱",
	[":bosslianyu"] = "结束阶段开始时，你可以对所有其他角色各造成1点火焰伤害。",

	["#boss_heiwuchang"] = "Boss Lv.3",
	["boss_heiwuchang"] = "黑无常",
	["bosstaiping"] = "太平",
	[":bosstaiping"] = "锁定技。摸牌阶段，你额外摸两张牌。",
	["bosssuoming"] = "索命",
	[":bosssuoming"] = "结束阶段开始时，你可以横置所有不处于连环状态的其他角色的武将牌。",
	["bossxixing"] = "吸星",
	[":bossxixing"] = "准备阶段开始时，你可以对一名处于连环状态的其他角色造成1点雷电伤害，然后你回复1点体力。",
	["bossxixing-invoke"] = "你可以发动“吸星”<br/> <b>操作提示</b>: 选择一名处于连环状态的其他角色→点击确定<br/>",

	["#boss_baiwuchang"] = "Boss Lv.3",
	["boss_baiwuchang"] = "白无常",
	["bossqiangzheng"] = "强征",
	[":bossqiangzheng"] = "结束阶段开始时，你可以获得所有其他角色各一张手牌。",
	["bosszuijiu"] = "醉酒",
	[":bosszuijiu"] = "锁定技。你使用【杀】将要造成的伤害+1。",
	["#ZuijiuBuff"] = "%from 的“<font color=\"yellow\"><b>醉酒</b></font>”被触发，对 %to 造成的伤害从 %arg 点增加至 %arg2 点",

	["#boss_luocha"] = "Boss Lv.4",
	["boss_luocha"] = "罗刹",
	["bossmodao"] = "魔道",
	[":bossmodao"] = "锁定技。准备阶段开始时，你摸两张牌。",
	["bossqushou"] = "驱兽",
	[":bossqushou"] = "出牌阶段开始时，你可以视为使用一张【南蛮入侵】。",

	["#boss_yecha"] = "Boss Lv.4",
	["boss_yecha"] = "夜叉",
	["bossmojian"] = "魔箭",
	[":bossmojian"] = "出牌阶段开始时，你可以视为使用一张【万箭齐发】。",
	["bossdanshu"] = "丹术",
	[":bossdanshu"] = "每当你于回合外失去牌后，你可以进行判定：若结果为红色，你回复1点体力。",

	["BossModeExpStore"] = "闯关模式：经验值提升能力",
	["BossModeExpStore:drawcard"] = "摸一张牌",
	["BossModeExpStore:recover"] = "回复1点体力",
	["BossModeExpStore:maxhp"] = "增加1点体力上限",
	["BossModeExpStore:recovermaxhp"] = "回复体力增加上限",
	["BossModeExpStore:acquireskill"] = "获得技能",
	["BossModeExpStore:cancel"] = "完成，进入下一关",
	["BossModeExpStoreSkillDetach"] = "失去技能",
	["skill"] = "技能",
	["nosskill"] = "-旧",
	["#UseExpPoint"] = "%from 使用了 %arg 点经验 %arg2",
	["BossLevelA"] = "第",
	["BossLevelB"] = "关",
	["(acquired)"] = "(已获得)",
}
