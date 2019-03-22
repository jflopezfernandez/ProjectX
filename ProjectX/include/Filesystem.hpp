
#ifndef PROJECTX_INCLUDES_FILESYSTEM_HPP_
#define PROJECTX_INCLUDES_FILESYSTEM_HPP_

namespace X
{
namespace Filesystem
{
    bool Exists(const FileSystem::path& p, FileSystem::file_status s = FileSystem::file_status{})
    {
        return (FileSystem::status_known(s) ? FileSystem::exists(s) : FileSystem::exists(p));
    }

    bool CreateDirectory(const FileSystem::path& p)
    {
        if (Exists(p)) {
            std::cerr << "The directory " << p << " already exists." << IO::endl;
            
            return false;
        }

        return FileSystem::create_directory(p);
    }
} // namespace Filesystem
} // namespace X

#endif // PROJECTX_INCLUDES_FILESYSTEM_HPP_
