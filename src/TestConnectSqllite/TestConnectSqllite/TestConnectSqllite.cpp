// TestConnectSqllite.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <sqlite3.h>
#include <iostream>

#pragma comment(lib,"sqlite3.lib")

int main()
{
	{

    std::cout << "Hello World!\n";
	sqlite3 *sql = NULL; // 一个打开的数据库实例
	const char * path = "test.db";//某个sql文件的路径

	// 根据文件路径打开数据库连接。如果数据库不存在，则创建。
	// 数据库文件的路径必须以C字符串传入。
	int result = sqlite3_open_v2(path, &sql, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);

	if (result == SQLITE_OK) {
		std::clog << "打开数据库连接成功";
	}
	else {
		std::clog << "打开数据库连接失败";
	}

	


	const char *sqlSentence = "CREATE TABLE IF NOT EXISTS t_person(id integer PRIMARY KEY AUTOINCREMENT, name text NOT NULL, age integer NOT NULL);";        //SQL语句
	sqlite3_stmt *stmt = NULL;        //stmt语句句柄

	//进行插入前的准备工作——检查语句合法性
	//-1代表系统会自动计算SQL语句的长度
	result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);

	if (result == SQLITE_OK) {
		std::clog << "添加数据语句OK";
		//执行该语句
		sqlite3_step(stmt);
	}
	else {
		std::clog << "添加数据语句有问题";
	}
	//清理语句句柄，准备执行下一个语句
	sqlite3_finalize(stmt);


	sqlSentence = "INSERT INTO t_person(name, age) VALUES('夏明', 22); ";        //SQL语句
	 stmt = NULL;        //stmt语句句柄

	//进行插入前的准备工作——检查语句合法性
	//-1代表系统会自动计算SQL语句的长度
	 result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);

	if (result == SQLITE_OK) {
		std::clog << "添加数据语句OK";
		//执行该语句
		sqlite3_step(stmt);
	}
	else {
		std::clog << "添加数据语句有问题";
	}
	//清理语句句柄，准备执行下一个语句
	sqlite3_finalize(stmt);


	sqlSentence = "SELECT name, age FROM t_person WHERE age < 30;";    //SQL语句
	stmt = NULL;    // stmt语句句柄

	//进行查询前的准备工作——检查语句合法性
	//-1代表系统会自动计算SQL语句的长度
	 result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);

	if (result == SQLITE_OK) {
		std::clog << "查询语句OK";
		// 每调一次sqlite3_step()函数，stmt语句句柄就会指向下一条记录
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			// 取出第0列字段的值
			const unsigned char *name = sqlite3_column_text(stmt, 0);
			// 取出第1列字段的值
			int age = sqlite3_column_int(stmt, 1);
			//输出相关查询的数据
			std::clog << "name = " << name << ", age = " << age;
		}
	}
	else {
		std::clog << "查询语句有问题";
	}
	//清理语句句柄，准备执行下一个语句
	sqlite3_finalize(stmt);

	//关闭数据库
	if (sql) {
		       sqlite3_close_v2(sql);
		       sql = nullptr;
		
	}

	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
