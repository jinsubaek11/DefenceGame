#include "BossEnemyPool.h"
#include "PooledBossEnemy.h"


ABossEnemyPool::ABossEnemyPool()
{
	classType = APooledBossEnemy::StaticClass();
	poolSize = 1;
}