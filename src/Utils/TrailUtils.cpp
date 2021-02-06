#include "Utils/TrailUtils.hpp"
#include "GlobalNamespace/SaberTrail.hpp"
#include "Trail/QosmeticsTrail.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/MeshFilter.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"
#include "QosmeticsLogger.hpp"

using namespace UnityEngine;
using namespace Qosmetics;

static Il2CppString* trailName = nullptr;

#define INFO(value...) QosmeticsLogger::GetContextLogger("Trail Utils").info(value)
#define ERROR(value...) QosmeticsLogger::GetContextLogger("Trail Utils").error(value)

GlobalNamespace::SaberTrailRenderer* TrailUtils::NewTrailRenderer(Material* mat)
{
    // make a new gameobject to house the prefab on
    GameObject* newPrefab = GameObject::New_ctor();
    // Trail renderer script holds reference to meshfilter and meshrenderer used to render the trial
    newPrefab->AddComponent<MeshFilter*>();
    newPrefab->AddComponent<MeshRenderer*>();
    
    GlobalNamespace::SaberTrailRenderer* trailRendererPrefab = newPrefab->AddComponent<GlobalNamespace::SaberTrailRenderer*>();
    
    // set the material
    trailRendererPrefab->meshRenderer->set_material(mat);      
    // give it a good name, for identification I guess
    if (!trailName) trailName = il2cpp_utils::createcsstr("Trail", il2cpp_utils::StringType::Manual);
    newPrefab->set_name(trailName);
    // return the trail renderer pointer
    return trailRendererPrefab;
}

void TrailUtils::RemoveTrail(Transform* obj)
{
    if (!obj) return;
    GlobalNamespace::SaberTrail* trail = nullptr;
    Array<GlobalNamespace::SaberTrail*>* trails = obj->get_gameObject()->GetComponents<GlobalNamespace::SaberTrail*>();

    if (trails)
    {
        QosmeticsTrail* customTrail = obj->get_gameObject()->GetComponent<QosmeticsTrail*>();
        for (int i = 0; i < trails->Length(); i++)
        {
            trail = trails->values[i];
            if (trail && trail != customTrail)
            {
                trail->trailDuration = 0.0f;
                trail->whiteSectionMaxDuration = 0.0f;
                trail->set_enabled(false);
            }
        }
    }    
}