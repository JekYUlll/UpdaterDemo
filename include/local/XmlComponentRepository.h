//
// Created by horeb on 25-4-19.
//

#ifndef XMLCOMPONENTREPOSITORY_H
#define XMLCOMPONENTREPOSITORY_H

#include "IComponentRepository.h"
#include "core/UpdateManager.h"
#include "tinyxml2.h"

namespace udc {

class XmlComponentRepository final : public IComponentRepository {
  public:
    explicit XmlComponentRepository(const std::string_view xmlPath)
        : m_xmlPath(xmlPath) {}

    ~XmlComponentRepository() override = default;

    Components load() override {
        using namespace tinyxml2;
        Components comps;
        XMLDocument doc;
        if (doc.LoadFile(m_xmlPath.c_str()) != XML_SUCCESS) {
            LOG_E("Failed to load xml file {}", m_xmlPath);
            return comps;
        }
        XMLElement* root = doc.FirstChildElement("Packages");
        if (!root) return comps;

        if (auto* name = root->FirstChildElement("ApplicationName"))
            comps.applicationName = name->GetText() ? name->GetText() : "";

        if (auto* ver = root->FirstChildElement("ApplicationVersion"))
            comps.applicationVersion = Version::parse(ver->GetText() ? ver->GetText() : "");

        for (auto* e = root->FirstChildElement("Package"); e; e = e->NextSiblingElement("Package")) {
            LocalPackage p;

            if (auto* n = e->FirstChildElement("Name"))            p.name = n->GetText() ? n->GetText() : "";
            if (auto* t = e->FirstChildElement("Title"))           p.title = t->GetText() ? t->GetText() : "";
            if (auto* d = e->FirstChildElement("Description"))     p.description = d->GetText() ? d->GetText() : "";
            if (auto* v = e->FirstChildElement("Version"))         p.version = Version::parse(v->GetText() ? v->GetText() : "");
            if (auto* l = e->FirstChildElement("LastUpdateDate"))  p.lastUpdateDate = Date::parse(l->GetText() ? l->GetText() : "");
            if (auto* i = e->FirstChildElement("InstallDate"))     p.installDate = Date::parse(i->GetText() ? i->GetText() : "");
            if (auto* s = e->FirstChildElement("Size"))            p.size = s->GetText() ? std::stoi(s->GetText()) : 0;
            if (auto* c = e->FirstChildElement("Checkable"))       p.checkable = c->GetText() && std::string(c->GetText()) == "true";

            comps.packages.push_back(std::move(p));
        }

        return comps;
    }

    // todo 在别处安装/删除本地的包后返回一个Components，用于此处更新
    void save(const Components& comps) override {
        using namespace tinyxml2;
        XMLDocument doc;
        auto* root = doc.NewElement("Packages");
        doc.InsertFirstChild(root);

        auto* name = doc.NewElement("ApplicationName");
        name->SetText(comps.applicationName.c_str());
        root->InsertEndChild(name);

        auto* ver = doc.NewElement("ApplicationVersion");
        ver->SetText(comps.applicationVersion.toString().c_str());
        root->InsertEndChild(ver);

        for (const auto& p : comps.packages) {
            auto* e = doc.NewElement("Package");

            auto* n = doc.NewElement("Name");             n->SetText(p.name.c_str());             e->InsertEndChild(n);
            auto* t = doc.NewElement("Title");            t->SetText(p.title.c_str());            e->InsertEndChild(t);
            auto* d = doc.NewElement("Description");      d->SetText(p.description.c_str());      e->InsertEndChild(d);
            auto* v = doc.NewElement("Version");          v->SetText(p.version.toString().c_str()); e->InsertEndChild(v);
            auto* l = doc.NewElement("LastUpdateDate");   l->SetText(p.lastUpdateDate.toString().c_str()); e->InsertEndChild(l);
            auto* i = doc.NewElement("InstallDate");      i->SetText(p.installDate.toString().c_str()); e->InsertEndChild(i);
            auto* s = doc.NewElement("Size");             s->SetText(std::to_string(p.size).c_str()); e->InsertEndChild(s);
            auto* c = doc.NewElement("Checkable");        c->SetText(p.checkable ? "true" : "false"); e->InsertEndChild(c);

            root->InsertEndChild(e);
        }

        doc.SaveFile(m_xmlPath.c_str());
    }

  private:
    std::string m_xmlPath;
};

} // namespace udc

#endif // XMLCOMPONENTREPOSITORY_H
