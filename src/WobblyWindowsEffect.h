/*
 * Copyright (C) 2018 Vlad Zagorodniy <vladzzag@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// kwineffects
#include <kwineffects.h>

// libanimation
#include <wobbly/wobbly.h>

class WobblyWindowsEffect : public KWin::Effect {
    Q_OBJECT

public:
    WobblyWindowsEffect();
    ~WobblyWindowsEffect() override;

    void reconfigure(ReconfigureFlags flags) override;

    void prePaintScreen(KWin::ScreenPrePaintData& data, int time) override;
    void postPaintScreen() override;

    void prePaintWindow(KWin::EffectWindow* w, KWin::WindowPrePaintData& data, int time) override;
    void paintWindow(KWin::EffectWindow* w, int mask, QRegion region, KWin::WindowPaintData& data) override;

    bool isActive() const override;
    int requestedEffectChainPosition() const override;

private Q_SLOTS:
    void slotWindowStartUserMovedResized(KWin::EffectWindow* w);
    void slotWindowStepUserMovedResized(KWin::EffectWindow* w, const QRect& geometry);
    void slotWindowFinishUserMovedResized(KWin::EffectWindow* w);
    void slotWindowGeometryShapeChanged(KWin::EffectWindow* w, const QRect& old);
    void slotWindowMaximizedStateChanged(KWin::EffectWindow* w, bool horizontal, bool vertical);
    void slotWindowDeleted(KWin::EffectWindow* w);

private:
    int m_gridResolution;
    wobbly::Model::Settings m_settings;

    struct AnimationData {
        QSharedPointer<wobbly::Model> model;
        QSharedPointer<wobbly::Anchor> grabAnchor;
        QPointF lastGrabPosition;
        bool stable;
        bool destroyable;
    };

    QHash<KWin::EffectWindow*, AnimationData> m_animations;
};

inline int WobblyWindowsEffect::requestedEffectChainPosition() const
{
    return 55;
}
