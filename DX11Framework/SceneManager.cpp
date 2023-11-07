#include "sceneManager.h"
#include "ModelManager.h"
#include "ObjectManager.h"
#include "Renderer.h"
#include "Camera.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Monkey.h"
#include <string>

//Tells  yaml it is a .lib with no .dll
#define YAML_CPP_STATIC_DEFINE
#include "yaml-cpp/yaml.h"
//Functionally equivalent to adding dependency in project
#pragma comment(lib, "lib\\x64\\yaml-cppd.lib")


SceneManager::SceneManager() {

}

SceneManager::~SceneManager() {
    delete _objectManager;
    delete _modelManager;

    delete _cam;
}

HRESULT SceneManager::Initialise(Renderer* renderer) {
    HRESULT hr = S_OK;

    _renderManager = renderer;

    // ModelManager Init
    _modelManager = new ModelManager();
    _modelManager->SetRenderManager(renderer);
    _modelManager->Initialise();

    // ObjManager Init
    _objectManager = new ObjectManager();
    _objectManager->SetRenderManager(renderer);
    _objectManager->SetModelManager(_modelManager);
    InitHardcodedObjects(); // Renderer Class

    // Camera Init
    XMFLOAT3X3 CamPos = XMFLOAT3X3(0, 0, -10.0f, // eye
        0, 0, 0, // at
        0, 1, 0); // up

    _cam = new Camera(CamPos);
    _renderManager->SetCamera(_cam);

    return hr;
}

void SceneManager::Update(float deltaTime) {
    _objectManager->Update(deltaTime);
}

void SceneManager::InitHardcodedObjects() {
    Texture* defaultTexture = _modelManager->GetTexture("Default");

    Object* cube = new Cube();
    cube->SetName("Test Cube");
    _objectManager->AddObject(cube, XMFLOAT3(5.0f, 0.0f, 0.0f));
    Texture* tex = _modelManager->GetTexture("Crate");
    cube->SetTexture(tex);

    Pyramid* _pyramid = new Pyramid();
    _pyramid->SetName("Test Pyramid");
    _objectManager->AddObject(_pyramid, XMFLOAT3(-3.0f, 0.0f, 5.0f));

    cube->SetParent(_pyramid);

    Monkey* monkey = new Monkey();
    monkey->SetName("Monkey");
    _objectManager->AddObject(monkey, XMFLOAT3(-5, 0.0f, 5.0f));
    monkey->GetModel()->SetShader("VertexShading");

    Monkey* monkey2 = new Monkey();
    monkey2->SetName("Monkey2");
    _modelManager->LoadModelFromFile("monkey.obj", "Monkey2");
    _objectManager->AddObject(monkey2, XMFLOAT3(5, 0.0f, 5.0f));

    //Object* photogrammetry = new Object();
    //photogrammetry->SetName("Photogrammetry");
    //_modelManager->LoadModelFromFile("photogrammetry.obj", "Photogrammetry");
    //_objectManager->AddObject(photogrammetry, XMFLOAT3(0.0f, -80.0f, 0.0f));
    //Texture* photoTex = _modelManager->GetTexture("photogrammetry");
    //photogrammetry->SetTexture(photoTex);

    Object* plane = new Object();
    plane->SetName("Plane");
    plane->SetColor(XMFLOAT4(0.05f, 0.1f, 0.1f, 1.0f));

    _modelManager->LoadModelFromFile("plane.obj", "Plane");
    _objectManager->AddObject(plane, XMFLOAT3(0.0f, -5.0f, 0.0f));

    cube->transform->parent = _pyramid->transform;
}

Transform* YAMLReadTransform(const YAML::Node& node) { // Okay I hated it's ugliness so I actually written it into a seperate function now.
    Transform* transform = new Transform();

    const YAML::Node nPosition = node["Position"];
    const YAML::Node nRotation = node["Rotation"];
    const YAML::Node nScale = node["Scale"];

    transform->position = XMFLOAT3(
        nPosition["x"].as<float>(),
        nPosition["y"].as<float>(),
        nPosition["z"].as<float>()
    );

    transform->rotation = XMFLOAT3(
        nRotation["x"].as<float>(),
        nRotation["y"].as<float>(),
        nRotation["z"].as<float>()
    );

    transform->scale = XMFLOAT3(
        nRotation["x"].as<float>(),
        nRotation["y"].as<float>(),
        nRotation["z"].as<float>()
    );

    return transform;
}

bool SceneManager::LoadScene(const char* path) {
    // Load yaml.
    std::string fullPath = "Levels\\";
    fullPath.append(path);
    fullPath.append(".yaml");
    
    YAML::Node levelFile = YAML::LoadFile(fullPath.c_str());
    
    /// https://github.com/jbeder/yaml-cpp/wiki/Tutorial#basic-parsing-and-node-editing using the iterator example provided.
    /// Kind of, seems like YAML is made out of nodes so I can iterate through a node for the model node and read that node.
    /// First time using YAML without a very simplified helper so this is quite easy to comprehend.

    //  File Structure so far:
    /// Shaders
    ///    ShaderName
    /// Textures
    ///    TextureName
    /// Models
    ///    Model[]
    ///      Name
    ///      ObjPath
    ///      Shader
    ///      Texture
    ///      Transform
    ///          Position
    ///          Rotation
    ///          Scale
    /// Lights
    ///    Light[]
    ///      position
    ///      rotation
    ///      Type
    ///      Falloff
    ///      
    /// Objects
    ///    Object[]
    ///      Name
    ///      ModelName
    ///      Transform
    ///          Position
    ///          Rotation
    ///          Scale
    ///      
    ///      

    // SHADER
    { 
        const YAML::Node shaders = levelFile["shaders"];

        for (YAML::const_iterator it = shaders.begin(); it != shaders.end(); it++) {
            const YAML::Node shader = *it;

            _modelManager->CreateShader(shader["Name"].as<std::string>());
        }
    }

    // TEXTURE
    { 

    }

    // MODEL
    { 
        // Get list of models to load:
        const YAML::Node models = levelFile["models"];

        // Load all the models in the Model Manager
        for (YAML::const_iterator it = models.begin(); it != models.end(); it++) {
            const YAML::Node model = *it;
            // Load .obj file.
            Model* modelObj = _modelManager->LoadModelFromFile(model["ObjPath"].as<std::string>(), model["Name"].as<std::string>());

            // Get shader.
            Shader* shader = _modelManager->GetShader(model["Shader"].as<std::string>());
            if (shader == nullptr) {
                throw new std::exception("Shader not found");
                return false;
            }

            // Get texture.
            Texture* texture = _modelManager->GetTexture(model["Texture"].as<std::string>());

            // Get transform.
            Transform* transform = YAMLReadTransform(model["Transform"]);

            // Set Shader, Texture & Transformation
            modelObj->SetShader(shader);
            modelObj->SetTexture(texture);
            modelObj->transform = transform;
        }
    }

    // TODO: LIGHT
    {

    }

    // OBJECT
    {

    }

    return true;
}