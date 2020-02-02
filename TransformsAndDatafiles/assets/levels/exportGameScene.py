import json
import maya.cmds as cmds
import math

def matrix_to_quat(m):
    w = math.sqrt(1.0 + m[0] + m[5] + m[10]) / 2.0
    w4 = w * 4.0
    x = (m[6] - m[9]) / w4
    y = (m[8] - m[2]) / w4
    z = (m[1] - m[4]) / w4
    return [w, x, y, z]

jsonData = {}  
jsonData['GameObjects'] = []  

selected_obj = cmds.ls(sl=True, type='transform')
for curr_obj in selected_obj:
    translation = cmds.xform(curr_obj, query=True, translation=True, worldSpace=True)
    transformationMatrix = cmds.xform(curr_obj, query=True, matrix=True)
    orientation = matrix_to_quat(transformationMatrix)
    gameObjectName = ""
    gameObjectType = ""
    gameObjectPath = ""
    if curr_obj.find("duck") >= 0:
        gameObjectType = "PlayerCharacter"
        gameObjectName = "duck"
        gameObjectPath = "assets/models/Duck.dae"
        orientation = [1,0,0,0]
    elif curr_obj.find("PeeblesR") >= 0:
        gameObjectType = "RotatingEnvironmentObject"
        gameObjectName = "PeeblesR"
        gameObjectPath = "assets/models/Peebles.obj"
    elif curr_obj.find("TreeR") >= 0:
        gameObjectType = "RotatingEnvironmentObject"
        gameObjectName = "TreeR"
        gameObjectPath = "assets/models/Tree_A.obj"
    elif curr_obj.find("RockR") >= 0:
        gameObjectType = "RotatingEnvironmentObject"
        gameObjectName = "RockR"
        gameObjectPath = "assets/models/Rock_A.obj"
    elif curr_obj.find("PeeblesM") >= 0:
        gameObjectType = "MovingEnvironmentObject"
        gameObjectName = "PeeblesM"
        gameObjectPath = "assets/models/Peebles.obj"
    elif curr_obj.find("TreeM") >= 0:
        gameObjectType = "MovingEnvironmentObject"
        gameObjectName = "TreeM"
        gameObjectPath = "assets/models/Tree_A.obj"
    elif curr_obj.find("RockM") >= 0:
        gameObjectType = "MovingEnvironmentObject"
        gameObjectName = "RockM"
        gameObjectPath = "assets/models/Rock_A.obj"
    elif curr_obj.find("floor") >= 0:
        gameObjectType = "StaticEnvironmentObject"
        gameObjectName = "floor"
        gameObjectPath = "assets/models/floor.dae"
    elif curr_obj.find("Peebles") >= 0:
        gameObjectType = "StaticEnvironmentObject"
        gameObjectName = "Peebles"
        gameObjectPath = "assets/models/Peebles.obj"
    elif curr_obj.find("Tree") >= 0:
        gameObjectType = "StaticEnvironmentObject"
        gameObjectName = "Tree"
        gameObjectPath = "assets/models/Tree_A.obj"
    elif curr_obj.find("Rock") >= 0:
        gameObjectType = "StaticEnvironmentObject"
        gameObjectName = "Rock"
        gameObjectPath = "assets/models/Rock_A.obj"
   
    
    if gameObjectType != "":
        jsonData['GameObjects'].append({
            'name': gameObjectName,
            'type': gameObjectType,
            'path': gameObjectPath,
            'position': [translation[0], translation[1], translation[2]],
            'orientation': [orientation[0], orientation[1], orientation[2], orientation[3]]
            
})


print jsonData

with open('H:\Desktop\Level.json', 'w') as outfile:
    json.dump(jsonData, outfile, sort_keys=True, indent=2)