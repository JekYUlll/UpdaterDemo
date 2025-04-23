//
// Created by horeb on 25-4-17.
//

#ifndef XMLUPDATEPROVIDER_H
#define XMLUPDATEPROVIDER_H

#include "IUpdateProvider.h"

#include <utility>
#include <tinyxml2.h>
#include <memory>

namespace udc {

class XmlUpdateProvider final : public IUpdateProvider {
  public:
    XmlUpdateProvider(const std::string_view repoUrl, const std::shared_ptr<INetworkAccess>& networkAccess)
        : m_repoUrl(repoUrl),
          m_net(networkAccess) {}

    ~XmlUpdateProvider() override = default;

    std::string fetch() override {
        return m_net->downloadText(m_repoUrl + "Updates.xml");
    }

    Updates parse(const std::string& xml) override {
        using namespace tinyxml2;
        XMLDocument doc;
        doc.Parse(xml.c_str());
        Updates result{};
        XMLElement* root = doc.FirstChildElement("Updates");
        if (!root)
            return result;
        result.applicationName =
            root->FirstChildElement("ApplicationName")->GetText();
        result.applicationVersion =
            Version(root->FirstChildElement("ApplicationVersion")->GetText());
        result.bChecksum =
            root->FirstChildElement("Checksum")->GetText() == "true";

        for (XMLElement* pkg = root->FirstChildElement("PackageUpdate");
             pkg != nullptr; pkg = pkg->NextSiblingElement("PackageUpdate")) {
            PackageUpdate p;
            fillPackageUpdate(pkg, p);
            result.packages.push_back(std::move(p));
        }

        return result;
    }

  private:
    static void fillPackageUpdate(tinyxml2::XMLElement* pkg, PackageUpdate& p) {
        using namespace tinyxml2;
        p.name = pkg->FirstChildElement("Name")->GetText();
        p.displayName = pkg->FirstChildElement("DisplayName")->GetText();
        p.description = pkg->FirstChildElement("Description")->GetText();
        p.version = Version(pkg->FirstChildElement("Version")->GetText());
        p.releaseDate = pkg->FirstChildElement("ReleaseDate")->GetText();
        p.isDefault = pkg->FirstChildElement("Default")->GetText();
        XMLElement* updateFileElem = pkg->FirstChildElement("UpdateFile");
        if (updateFileElem) {
            const char* os = updateFileElem->Attribute("OS");
            if (os) {
                p.updateFile.os = os;
            }
            updateFileElem->QueryIntAttribute("CompressedSize",
                                              &p.updateFile.compressedSize);
            updateFileElem->QueryIntAttribute("UncompressedSize",
                                              &p.updateFile.uncompressedSize);
        }
        p.downloadableArchives =
            pkg->FirstChildElement("DownloadableArchives")->GetText();
        p.sha1 = pkg->FirstChildElement("SHA1")->GetText();
    }

    std::string m_repoUrl;
    std::shared_ptr<INetworkAccess> m_net;
};

} // namespace udc

#endif // XMLUPDATEPROVIDER_H
