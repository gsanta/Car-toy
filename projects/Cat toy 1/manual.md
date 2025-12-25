# How to print mm precise images with the printer

## Blender

1. Set units to millimeters

Scene Properties → Units → Metric

Unit Scale = 0.001
Length = mm

2. Use an Orthographic camera

Camera Properties → Type: Orthographic

Ortho Scale = width in mm you want to print
(e.g., 50 mm)

Set render resolution

Resolution X / Y = (mm / 25.4) × DPI
(e.g., 50 mm / 25.4 × 300 DPI ≈ 590 px)

Pixel Density = target DPI (e.g., 300) — this is metadata only

Frame the camera

Numpad 0 → Camera view

Render the image

Render → Render Image (F12)

Save via Image → Save As → PNG

## Inkspace

Open PNG in Inkscape

File → Open (do not import)

Units: mm (File → Document Properties → Display units: mm)

Check the size

Select the image

Toolbar / Transform → Width = 50 mm, Height = 50 mm

Resize page to content

File → Document Properties → Resize page to content → Apply

Now page = exactly image size (50 × 50 mm)

File → Save As → PDF

Options: defaults are fine

Rasterize filters → OFF (if dialog appears)