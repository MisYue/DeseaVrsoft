-- Drop table
drop table WARHEAD cascade constraints;
-- Create table
create table WARHEAD
(
  warheadid           NUMBER(5) not null,
  warheadguid         CHAR(50) not null,
  name                CHAR(50) not null,
  projectguid         CHAR(50),
  country             CHAR(20),
  warheadsubclassguid CHAR(50) not null,
  describe            CHAR(500),
  missilename         CHAR(50),
  attendedstarttime   DATE,
  attendedendtime     DATE,
  warhead2dxml        BLOB not null,
  warheadpowercsv     BLOB
)
tablespace SYSTEM
  pctfree 10
  pctused 40
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    next 1M
    minextents 1
    maxextents unlimited
  );
-- Create/Recreate primary, unique and foreign key constraints 
alter table WARHEAD
  add constraint PK_WARHEADID primary key (WARHEADID)
  using index 
  tablespace SYSTEM
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    next 1M
    minextents 1
    maxextents unlimited
  );
