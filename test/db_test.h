#include <list>
#include <memory>
#include <string>
#include <iostream>
#include <sqlite3.h>
#include <gtest/gtest.h>

#include "../src/triangle.h"
#include "../src/drawing.h"
#include "../src/unit_of_work.h"
#include "../src/drawing_mapper.h"
#include "../src/painter_mapper.h"

class DBSuite : public ::testing::Test {
protected:
    void SetUp() override {
        create_drawing_table();
        create_painter_table();
        populate_drawings();
        populate_painters();
        dm = DrawingMapper::instance();
        dm->setDB("resource/drawing.db");
        pm = PainterMapper::instance();
        pm->setDB("resource/painter.db");
    }

    void TearDown() override {
        drop_drawing_table();
        drop_painter_table();
        sqlite3_close(db);
        sqlite3_close(db_p);
    }

    void create_drawing_table() {
        ASSERT_EQ(0, sqlite3_open("resource/drawing.db", &db));
        const char *stmt = "CREATE TABLE drawing ("
                           "ID         char(6) PRIMARY KEY     not null,"
                           "painter    varchar(50)             not null,"
                           "shapes varchar(1028),"
                           "FOREIGN KEY(painter) REFERENCES painter(ID))";
        int rc = sqlite3_exec(db, stmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void drop_drawing_table() {
        const char *dropStmt = "DROP TABLE drawing";
        int rc = sqlite3_exec(db, dropStmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void create_painter_table() {
        ASSERT_EQ(0, sqlite3_open("resource/painter.db", &db_p));
        const char *stmt = "CREATE TABLE painter ("
                           "ID         char(6) PRIMARY KEY     not null,"
                           "name    varchar(50)             not null)";
        int rc = sqlite3_exec(db_p, stmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void drop_painter_table() {
        const char *dropStmt = "DROP TABLE painter";
        int rc = sqlite3_exec(db_p, dropStmt, NULL, NULL, &err_msg);
        display_err_msg_and_fail_if_any(rc);
    }

    void populate_drawings() {
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

    void populate_painters() {
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

    void display_err_msg_and_fail_if_any(int rc) {
        if (rc)
        {
            std::cout << "db error: " << err_msg << std::endl;
            sqlite3_free(err_msg);
        }
        ASSERT_EQ(SQLITE_OK, rc);
    }

    void assert_status(std::string id, std::string true_status) {
        if(true_status == "inNew") {
            ASSERT_TRUE(UnitOfWork::instance()->inNew(id));
            ASSERT_FALSE(UnitOfWork::instance()->inClean(id));
            ASSERT_FALSE(UnitOfWork::instance()->inDirty(id));
            ASSERT_FALSE(UnitOfWork::instance()->inDeleted(id));
        }
        else if(true_status == "inClean") {
            ASSERT_FALSE(UnitOfWork::instance()->inNew(id));
            ASSERT_TRUE(UnitOfWork::instance()->inClean(id));
            ASSERT_FALSE(UnitOfWork::instance()->inDirty(id));
            ASSERT_FALSE(UnitOfWork::instance()->inDeleted(id));
        }
        else if(true_status == "inDirty") {
            ASSERT_FALSE(UnitOfWork::instance()->inNew(id));
            ASSERT_FALSE(UnitOfWork::instance()->inClean(id));
            ASSERT_TRUE(UnitOfWork::instance()->inDirty(id));
            ASSERT_FALSE(UnitOfWork::instance()->inDeleted(id));
        }
        else if(true_status == "inDeleted") {
            ASSERT_FALSE(UnitOfWork::instance()->inNew(id));
            ASSERT_FALSE(UnitOfWork::instance()->inClean(id));
            ASSERT_FALSE(UnitOfWork::instance()->inDirty(id));
            ASSERT_TRUE(UnitOfWork::instance()->inDeleted(id));
        } else if (true_status == "None") {
            ASSERT_FALSE(UnitOfWork::instance()->inNew(id));
            ASSERT_FALSE(UnitOfWork::instance()->inClean(id));
            ASSERT_FALSE(UnitOfWork::instance()->inDirty(id));
            ASSERT_FALSE(UnitOfWork::instance()->inDeleted(id));
        }
    }

    sqlite3 *db;
    sqlite3 *db_p;
    char *err_msg = nullptr;
    DrawingMapper *dm;
    PainterMapper *pm;
};

TEST_F(DBSuite, Sanity) {}

TEST_F(DBSuite, findDrawing) {
    Drawing *drawing = dm->find("d_0001");

    EXPECT_TRUE(UnitOfWork::instance()->inClean("d_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("d_0001"));
    EXPECT_TRUE(UnitOfWork::instance()->inClean("p_0001"));
    EXPECT_FALSE(UnitOfWork::instance()->inDirty("p_0001"));
    ASSERT_EQ(drawing->id(), "d_0001");
    ASSERT_EQ(drawing->getShape(0)->perimeter(), 3);
    ASSERT_EQ(drawing->painter()->id(), "p_0001");
    ASSERT_EQ(drawing->painter()->name(), "Patrick");
}

TEST_F(DBSuite, NewPainterAndFind) {
    Painter * newPainter = new Painter("p_0003", "John");
    assert_status(newPainter->id(), "inNew");

    UnitOfWork::instance()->commit();
    assert_status(newPainter->id(), "inClean");

    Painter * foundPainter = pm->find(newPainter->id());
    assert_status(foundPainter->id(), "inClean");
    ASSERT_EQ(foundPainter->id(), newPainter->id());
    ASSERT_EQ(foundPainter->name(), newPainter->name());
}

TEST_F(DBSuite, NewDrawingAndFind) {
    Painter * newPainter = pm->find("p_0003");
    Drawing * newDrawing = new Drawing("d_0004", newPainter);
    assert_status(newDrawing->id(), "inNew");

    UnitOfWork::instance()->commit();
    assert_status(newDrawing->id(), "inClean");

    Drawing * foundDrawing = dm->find(newDrawing->id());
    assert_status(foundDrawing->id(), "inClean");
    ASSERT_EQ(foundDrawing->id(), newDrawing->id());
    ASSERT_EQ(foundDrawing->painter()->id(), newDrawing->painter()->id());
    ASSERT_EQ(foundDrawing->painter()->name(), newDrawing->painter()->name());
    ASSERT_EQ(foundDrawing->getShape(0), nullptr);
    ASSERT_EQ(foundDrawing->getShapesAsString(), "");
}

TEST_F(DBSuite, NewDrawingWithShapesAndFind) {
    std::list<Shape *> newShapes = {
        new Triangle(1, 1, 1), 
        new Triangle(2, 2, 2)
    };
    Painter * newPainter = pm->find("p_0003");
    Drawing * newDrawing = new Drawing("d_0005", newPainter, newShapes);
    assert_status(newDrawing->id(), "inNew");

    UnitOfWork::instance()->commit();
    assert_status(newDrawing->id(), "inClean");

    Drawing * foundDrawing = dm->find(newDrawing->id());
    assert_status(foundDrawing->id(), "inClean");
    ASSERT_EQ(foundDrawing->id(), newDrawing->id());
    ASSERT_EQ(foundDrawing->painter()->id(), newDrawing->painter()->id());
    ASSERT_EQ(foundDrawing->painter()->name(), newDrawing->painter()->name());
    ASSERT_EQ(foundDrawing->getShape(0)->perimeter(), newDrawing->getShape(0)->perimeter());
    ASSERT_EQ(foundDrawing->getShape(1)->perimeter(), newDrawing->getShape(1)->perimeter());
    ASSERT_EQ(foundDrawing->getShape(2), nullptr);
    ASSERT_EQ(foundDrawing->getShapesAsString(), newDrawing->getShapesAsString());
}

TEST_F(DBSuite, findPainterAndUpdate) {
    Painter * painter = pm->find("p_0001");
    assert_status(painter->id(), "inClean");

    painter->setName("Patrick2");
    assert_status(painter->id(), "inDirty");

    UnitOfWork::instance()->commit();
    assert_status(painter->id(), "inClean");
    ASSERT_EQ(painter->id(), "p_0001");
    ASSERT_EQ(painter->name(), "Patrick2");
}

TEST_F(DBSuite, findDrawingAndUpdate) {
    Drawing * drawing = dm->find("d_0004");
    assert_status(drawing->id(), "inClean");

    drawing->setPainter(pm->find("p_0003"));
    assert_status(drawing->id(), "inDirty");

    UnitOfWork::instance()->commit();
    assert_status(drawing->id(), "inClean");
    ASSERT_EQ(drawing->id(), "d_0004");
    ASSERT_EQ(drawing->painter()->id(), "p_0003");
    ASSERT_EQ(drawing->painter()->name(), "John");
}

TEST_F(DBSuite, DeletePainterInClean) {
    Painter * painter = pm->find("p_0003");
    assert_status(painter->id(), "inClean");

    pm->del(painter->id());
    assert_status(painter->id(), "inDeleted");

    UnitOfWork::instance()->commit();
    assert_status(painter->id(), "None");
    ASSERT_EQ(pm->find("p_0003"), nullptr);
}

TEST_F(DBSuite, DeletePainterInNewWithoutCommit) {

    Painter * newPainter = new Painter("p_0003", "John");
    assert_status(newPainter->id(), "inNew");

    UnitOfWork::instance()->registerDeleted(newPainter);
    assert_status(newPainter->id(), "inDeleted");

    UnitOfWork::instance()->commit();
    assert_status(newPainter->id(), "None");
    ASSERT_EQ(pm->find(newPainter->id()), nullptr); 
}


