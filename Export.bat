@echo off
if not exist "ExportedContent" mkdir ExportedContent
if not exist "ExportedContent\Meshes" mkdir ExportedContent\Meshes
blender --background %1 --python Engine\Scripts\Editor\LevelExporter.py