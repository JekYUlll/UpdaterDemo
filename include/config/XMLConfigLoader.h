//
// Created by horeb on 25-4-21.
//

#ifndef XMLCONFIGLOADER_H
#define XMLCONFIGLOADER_H

#include "config/IConfigLoader.h"
#include "model/Repository.h"

#include <tinyxml2.h>

namespace udc {

class XMLConfigLoader final : public IConfigLoader {
  public:
    XMLConfigLoader() = default;
    ~XMLConfigLoader() override = default;

    Config loadFromFile(const std::string& path) override {
        using namespace tinyxml2;
        Config cfg;
        XMLDocument doc;
        if (doc.LoadFile(path.c_str()) != XML_SUCCESS) {
            throw std::runtime_error("Failed to load config.xml");
        }

        XMLElement* installer = doc.FirstChildElement("Installer");
        if (!installer)
            throw std::runtime_error("Missing <Installer>");

        auto getText = [](XMLElement* parent, const char* tag) -> std::string {
            if (auto* e = parent->FirstChildElement(tag)) {
                const char* text = e->GetText();
                return text ? text : "";
            }
            return "";
        };

        cfg.name = getText(installer, "Name");
        cfg.version = Version(getText(installer, "Version").c_str());
        cfg.targetDir = getText(installer, "TargetDir");

        XMLElement* remoteRepos =
            installer->FirstChildElement("RemoteRepositories");
        if (remoteRepos) {
            for (XMLElement* repoElem =
                     remoteRepos->FirstChildElement("Repository");
                 repoElem != nullptr;
                 repoElem = repoElem->NextSiblingElement("Repository")) {
                Repository repo;
                repo.url = getText(repoElem, "Url");
                repo.username = getText(repoElem, "Username");
                repo.password = getText(repoElem, "Password");
                repo.displayName = getText(repoElem, "DisplayName");

                const char* enabledText =
                    repoElem->FirstChildElement("Enabled")
                        ? repoElem->FirstChildElement("Enabled")->GetText()
                        : nullptr;
                repo.enabled =
                    enabledText ? std::string(enabledText) != "0" : true;

                cfg.repositories.push_back(std::move(repo));
            }
        }

        return cfg;
    }
};

} // namespace udc

#endif // XMLCONFIGLOADER_H
