/*
 * Copyright (C) 2000 Lars Knoll (knoll@kde.org)
 *           (C) 2000 Antti Koivisto (koivisto@kde.org)
 *           (C) 2000 Dirk Mueller (mueller@kde.org)
 *           (C) 2004 Allan Sandfeld Jensen (kde@carewolf.com)
 * Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2012 Apple Inc. All rights reserved.
 * Copyright (C) 2009 Google Inc. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#pragma once

#include "StyleDifference.h"

namespace WebCore {

enum class CursorDirective : uint8_t {
    SetCursorBasedOnStyle,
    SetCursor,
    DoNotSetCursor
};

enum class HitTestFilter : uint8_t {
    All,
    Self,
    Descendants
};

enum class HitTestAction : uint8_t {
    BlockBackground,
    ChildBlockBackground,
    ChildBlockBackgrounds,
    Float,
    Foreground
};

enum class MarkingBehavior : uint8_t {
    MarkOnlyThis,
    MarkContainingBlockChain,
};

enum class MapCoordinatesMode : uint8_t {
    IsFixed             = 1 << 0,
    UseTransforms       = 1 << 1,
    ApplyContainerFlip  = 1 << 2,
    IgnoreStickyOffsets = 1 << 3,
    ClampOverscroll     = 1 << 4,
};

enum class LayoutReason : uint8_t {
    None,
    Unknown,
    Initialize,
    WidthChanged,
    MinWidthChanged,
    MaxWidthChanged,
    HeightChanged,
    MinHeightChanged,
    MaxHeightChanged,
    VerticalAlignChanged,
    BoxSizingChanged,
    ZIndexChanged,
    StyleChanged,
    TextChanged,
};

inline LayoutReason toLayoutReason(Style::DifferenceProperty property)
{
    switch (property) {
        case Style::DifferenceProperty::Width:
            return LayoutReason::WidthChanged;
        case Style::DifferenceProperty::MinWidth:
            return LayoutReason::MinWidthChanged;
        case Style::DifferenceProperty::MaxWidth:
            return LayoutReason::MaxWidthChanged;
        case Style::DifferenceProperty::Height:
            return LayoutReason::HeightChanged;
        case Style::DifferenceProperty::MinHeight:
            return LayoutReason::MinHeightChanged;
        case Style::DifferenceProperty::MaxHeight:
            return LayoutReason::MaxHeightChanged;
        case Style::DifferenceProperty::VerticalAlign:
            return LayoutReason::VerticalAlignChanged;
        case Style::DifferenceProperty::BoxSizing:
            return LayoutReason::BoxSizingChanged;
        case Style::DifferenceProperty::ZIndex:
            return LayoutReason::ZIndexChanged;
        default:
            return LayoutReason::StyleChanged;
    }
}

}
