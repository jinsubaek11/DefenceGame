#include "NormalEnemyPool.h"
#include "PooledNormalEnemy.h"

ANormalEnemyPool::ANormalEnemyPool()
{
	classType = APooledNormalEnemy::StaticClass();
	poolSize = 5;
}