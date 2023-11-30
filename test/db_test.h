#include <gtest/gtest.h>

#include <sqlite3.h>
#include <string>
#include <iostream>

class Sqlite3Suite : public ::testing::Test {
protected:
  void SetUp() override {
    ASSERT_EQ(0, sqlite3_open("resource/test.db", &db));
    ASSERT_EQ(SQLITE_OK, sqlite3_prepare_v2(db, stmt1, nByte, &pStmt, &zTail));
    ASSERT_EQ(SQLITE_DONE, sqlite3_step(pStmt));
    ASSERT_EQ(SQLITE_OK, sqlite3_finalize(pStmt));
    ASSERT_EQ(SQLITE_OK, sqlite3_close(db));
  }

  void TearDown() override {
    ASSERT_EQ(0, sqlite3_open("resource/test.db", &db));
    ASSERT_EQ(SQLITE_OK, sqlite3_prepare_v2(db, dropStmt, nByte, &pStmt, &zTail));
    ASSERT_EQ(SQLITE_DONE, sqlite3_step(pStmt));
    ASSERT_EQ(SQLITE_OK, sqlite3_finalize(pStmt));
    ASSERT_EQ(SQLITE_OK, sqlite3_close(db));
  }

  sqlite3 *db;
  const char * stmt1 = "create table myTable (FirstName varchar(30), LastName varchar(30), Age smallint, Hometown varchar(30), Job varchar(30))";
  const char * dropStmt = "drop table myTable";
  int nByte = -1;
  sqlite3_stmt *pStmt;
  const char *zTail;

};

// TEST_F(Sqlite3Suite, libversionTest){
//   ASSERT_EQ(std::string("3.39.5"),  sqlite3_libversion());
// }

TEST_F(Sqlite3Suite, OpenAndCloseDBFile) {
  ASSERT_EQ(0, SQLITE_OK);
  ASSERT_EQ(0, sqlite3_open("resource/test.db", &db));
  ASSERT_EQ(SQLITE_OK, sqlite3_close(db));
}

TEST_F(Sqlite3Suite, PreparedStatement) {
  ASSERT_EQ(0, sqlite3_open("resource/test.db", &db));

  const char * stmt2 = "insert into myTable (FirstName, LastName, Age, Hometown, Job) values ('Peter', 'Griffin', 41, 'Quahog', 'Brewery')";
  const char * stmt3 = "insert into myTable (FirstName, LastName, Age, Hometown, Job) values ('Joseph', 'Swanson', 39, 'Quahog', 'Police Officer')";
  const char * stmt4 = "select * from myTable"; 

  ASSERT_EQ(SQLITE_OK, sqlite3_prepare_v2(db, stmt2, nByte, &pStmt, &zTail));
  ASSERT_EQ(SQLITE_DONE, sqlite3_step(pStmt));
  ASSERT_EQ(SQLITE_OK, sqlite3_finalize(pStmt));

  ASSERT_EQ(SQLITE_OK, sqlite3_prepare_v2(db, stmt3, nByte, &pStmt, &zTail));
  ASSERT_EQ(SQLITE_DONE, sqlite3_step(pStmt));
  ASSERT_EQ(SQLITE_OK, sqlite3_finalize(pStmt));

  ASSERT_EQ(SQLITE_OK, sqlite3_prepare_v2(db, stmt4, nByte, &pStmt, &zTail));
  ASSERT_EQ(SQLITE_ROW, sqlite3_step(pStmt));
  ASSERT_EQ(5, sqlite3_column_count(pStmt));
  ASSERT_EQ(std::string("Peter"), reinterpret_cast<const char*>(sqlite3_column_text(pStmt, 0)));
  ASSERT_EQ(SQLITE_ROW, sqlite3_step(pStmt));
  ASSERT_EQ(std::string("Joseph"), reinterpret_cast<const char*>(sqlite3_column_text(pStmt, 0)));

  ASSERT_EQ(SQLITE_OK, sqlite3_finalize(pStmt));

  ASSERT_EQ(SQLITE_OK, sqlite3_close(db));
}

class  Person {
public:
  Person(std::string fn, std::string ln, int age, std::string ht, std::string job): _first_name(fn), _last_name(ln), _age(age), _hometown(ht), _job(job) {

  }

  static Person * createPerson(std::string fn, std::string ln, int age, std::string ht, std::string job) {
    Person * p = new Person(fn, ln, age, ht, job);
    return p;
  }

  std::string toString() const {
    std::string r="";
    return r +_first_name + "\t" + _last_name + "\t" + std::to_string(_age) + "\t" + _hometown + "\t" + _job;
  }

private:
  std::string _first_name;
  std::string _last_name; 
  int _age; 
  std::string _hometown; 
  std::string _job;
};

int callback(void * not_used, int argc, char **argv, char **colNames) {
  for (int i = 0; i < argc; i++) {
    std::cout << colNames[i] << "\t"; 
  }
  std::cout << std::endl;

  Person * p = Person::createPerson(argv[0], argv[1], std::stoi(argv[2]), argv[3], argv[4]);
  std::cout << p->toString() << std::endl;

  return 0;

}

TEST_F(Sqlite3Suite, sqlite3_exec) {
  ASSERT_EQ(0, sqlite3_open("resource/test.db", &db));

  const char * stmt2 = "insert into myTable (FirstName, LastName, Age, Hometown, Job) values ('Peter', 'Lin', 41, 'Taipei', 'salesperson')";
  const char * stmt3 = "insert into myTable (FirstName, LastName, Age, Hometown, Job) values ('Joseph', 'Wang', 39, 'Taichung', 'chef')";
  const char * stmt4 = "select * from myTable"; 
  char * err_msg = nullptr;

  sqlite3_exec(db, stmt2, NULL, NULL, &err_msg);
  sqlite3_exec(db, stmt3, NULL, NULL, &err_msg);
  sqlite3_exec(db, stmt4, callback, NULL, &err_msg);

}