#include "StrongEnemyPool.h"
#include "PooledStrongEnemy.h"


AStrongEnemyPool::AStrongEnemyPool()
{
	classType = APooledStrongEnemy::StaticClass();
	poolSize = 2;
}