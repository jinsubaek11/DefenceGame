#include "WeakEnemyPool.h"
#include "PooledWeakEnemy.h"


AWeakEnemyPool::AWeakEnemyPool()
{
	classType = APooledWeakEnemy::StaticClass();
	poolSize = 50;
}