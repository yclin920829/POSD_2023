#include <gtest/gtest.h>
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <list>
#include <memory>
#include "../src/unit_of_work.h"
#include "../src/drawing_mapper.h"
#include "../src/painter_mapper.h"
#include "../src/drawing.h"

class DBSuite : public ::testing::Test
{
protected:
    void SetUp() override
    {
        create_drawing_table();
        create_painter_table();
        populate_drawings();
        populate_painters();
        dm = DrawingMapper::instance();
        dm->setDB("resource/drawing.db");
        pm = PainterMapper::instance();
        pm->setDB("resource/painter.db");
    }

    void TearDown() override
    {
        drop_drawing_table();
        drop_painter_table();
        sqlite3_close(db);
        sqlite3_close(db_p);
    }

    void create_drawing_table()
    {
        ASSERT_EQ(0, sqlite3_open("resource/drawing.db", &db));
        const char *stmt = "CREATE TABLE drawing ("
                           "ID         char(6) PRIMARY KEY     not null,"
                           "painter    varchar(50)             not null,"
                           "shapes varchar(1028),"
                           "FOREIGN KEY(painter) REFERENCES painter(ID))";
        int rc = sqlite3_exec(db, stmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void drop_drawing_table()
    {
        const char *dropStmt = "DROP TABLE drawing";
        int rc = sqlite3_exec(db, dropStmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void create_painter_table()
    {
        ASSERT_EQ(0, sqlite3_open("resource/painter.db", &db_p));
        const char *stmt = "CREATE TABLE painter ("
                           "ID         char(6) PRIMARY KEY     not null,"
                           "name    varchar(50)             not null)";
        int rc = sqlite3_exec(db_p, stmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void drop_painter_table()
    {
        const char *dropStmt = "DROP TABLE painter";
        int rc = sqlite3_exec(db_p, dropStmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void populate_drawings()
    {
        const char *s1 = "INSERT INTO drawing"
                         "(ID, painter, shapes)"
                         "values"
                         "('d_0001', 'p_0001', 'triangle 1 1 1')";
        int rc = sqlite3_exec(db, s1, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s2 = "INSERT INTO drawing"
                         "(ID,  painter,   shapes)"
                         "values"
                         "('d_0002', 'p_0001', 'triangle 2 2 2')";
        rc = sqlite3_exec(db, s2, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s3 = "INSERT INTO drawing"
                         "(ID,  painter,   shapes)"
                         "values"
                         "('d_0003', 'p_0002', 'compound { triangle 1 1 1 triangle 2 2 2 } triangle 3 3 3')";
        rc = sqlite3_exec(db, s3, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);
    }

    void populate_painters()
    {
        const char *s1 = "INSERT INTO painter"
                         "(ID, name)"
                         "values"
                         "('p_0001', 'Patrick')";
        int rc = sqlite3_exec(db_p, s1, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);

        const char *s2 = "INSERT INTO painter"
                         "(ID, name)"
                         "values"
                         "('p_0002', 'Mary')";
        rc = sqlite3_exec(db_p, s2, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
        ASSERT_EQ(SQLITE_OK, rc);
    }

    void display_err_msg_and_fail_if_any(int rc)
    {
        if (rc)
        {
            std::cout << "db error: " << err_msg << std::endl;
            sqlite3_free(err_msg);
        }
        ASSERT_EQ(SQLITE_OK, rc);
    }

    sqlite3 *db;
    sqlite3 *db_p;
    char *err_msg = nullptr;
    DrawingMapper *dm;
    PainterMapper *pm;
};

TEST_F(DBSuite, Sanity) {
    ASSERT_TRUE(true);
}

TEST_F(DBSuite, findDrawing)
{
    Drawing * drawing = dm->find("d_0001");

    EXPECT_TRUE(UnitOfWork::instance()->inClean("d_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("d_0001"));
    EXPECT_TRUE(UnitOfWork::instance()->inClean("p_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("p_0001"));
    ASSERT_EQ(drawing->id(), "d_0001");
    ASSERT_EQ(drawing->getShape(0)->perimeter(), 3);
    ASSERT_EQ(drawing->painter()->id(), "p_0001");
    ASSERT_EQ(drawing->painter()->name(), "Patrick");
}

// DBSuite.findPainterAndUpdate
TEST_F(DBSuite, findPainter)
{
    Painter * painter = pm->find("p_0001");

    EXPECT_TRUE(UnitOfWork::instance()->inClean("p_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("p_0001"));
    ASSERT_EQ(painter->id(), "p_0001");
    ASSERT_EQ(painter->name(), "Patrick");
}

TEST_F(DBSuite, UnitOfWorkRegisterDirty) {
    UnitOfWork * uow = UnitOfWork::instance();
    Drawing* drawing = dm->find("d_0001");
    Painter * painter = PainterMapper::instance()->find("p_0002");
    drawing->setPainter(painter);
    ASSERT_EQ(painter, drawing->painter());
    ASSERT_FALSE(uow->inClean("d_0001"));
    ASSERT_TRUE(uow->inDirty("d_0001"));

    uow->commit();
    ASSERT_EQ(painter, drawing->painter());
    ASSERT_TRUE(uow->inClean("d_0001"));
    ASSERT_FALSE(uow->inDirty("d_0001"));
}

TEST_F(DBSuite, UnitOfWorkRegisterNew) {
    Painter * painter = new Painter("p_0003", "Howard");
    UnitOfWork::instance()->registerNew(painter);
    ASSERT_TRUE(UnitOfWork::instance()->inNew("p_0003"));
    ASSERT_FALSE(UnitOfWork::instance()->inClean("p_0003"));
    ASSERT_FALSE(UnitOfWork::instance()->inDirty("p_0003"));
    ASSERT_FALSE(UnitOfWork::instance()->inDeleted("p_0003"));

    UnitOfWork::instance()->commit();

    ASSERT_FALSE(UnitOfWork::instance()->inNew("p_0003"));
    ASSERT_TRUE(UnitOfWork::instance()->inClean("p_0003"));
    ASSERT_FALSE(UnitOfWork::instance()->inDirty("p_0003"));
    ASSERT_FALSE(UnitOfWork::instance()->inDeleted("p_0003"));
}

TEST_F(DBSuite, update) {
    UnitOfWork * uow = UnitOfWork::instance();
    Painter * painter = PainterMapper::instance()->find("p_0002");
    painter->setName("joe");
    ASSERT_EQ("joe", painter->name());
    ASSERT_FALSE(UnitOfWork::instance()->inNew("p_0002"));
    ASSERT_FALSE(UnitOfWork::instance()->inClean("p_0002"));
    ASSERT_TRUE(UnitOfWork::instance()->inDirty("p_0002"));
    ASSERT_FALSE(UnitOfWork::instance()->inDeleted("p_0002"));

    uow->commit();

    ASSERT_FALSE(UnitOfWork::instance()->inNew("p_0002"));
    ASSERT_TRUE(UnitOfWork::instance()->inClean("p_0002"));
    ASSERT_FALSE(UnitOfWork::instance()->inDirty("p_0002"));
    ASSERT_FALSE(UnitOfWork::instance()->inDeleted("p_0002"));
}