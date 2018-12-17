#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QVector2D>

#include "mesh.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget
  : public QOpenGLWidget
  , protected QOpenGLFunctions
{
    Q_OBJECT

  public:
    GLWidget(QWidget* parent = nullptr);
    ~GLWidget() override;

    static bool isTransparent() { return m_transparent; }
    static void setTransparent(bool t) { m_transparent = t; }

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

  public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void cleanup();

  signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

  protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

  private:
    void setupVertexAttribs();
    void viewAll();
    QVector2D getNormalizedPosition(const QPoint& pos) const
    {
        return QVector2D(pos.x() / float(width()), pos.y() / float(height()));
    }

    int m_xRot;
    int m_yRot;
    int m_zRot;
    QPoint m_lastPos;
    QMatrix4x4 m_lastWworld;
    Mesh m_mesh;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_meshVbo;
    QOpenGLShaderProgram* m_program;
    int m_projMatrixLoc;
    int m_mvMatrixLoc;
    int m_normalMatrixLoc;
    int m_lightPosLoc;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
    static bool m_transparent;
};
