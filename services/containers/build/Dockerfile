FROM kitware/cmake:ci-fedora31-x86_64-2020-08-18

RUN dnf install -y https://download.postgresql.org/pub/repos/yum/reporpms/F-31-x86_64/pgdg-fedora-repo-latest.noarch.rpm
RUN dnf install -y libpq-devel postgresql11-server qt5 qt5-devel qt-creator