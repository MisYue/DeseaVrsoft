-- Create table
create table WARHEADCLASS
(
  warheadclassid   NUMBER(5) not null,
  warheadclassguid CHAR(50) not null,
  name             CHAR(50) not null,
  describe         CHAR(500)
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
alter table WARHEADCLASS
  add constraint PK_WCID primary key (WARHEADCLASSID)
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
